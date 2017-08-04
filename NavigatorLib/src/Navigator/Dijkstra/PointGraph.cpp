//
// Created by  Oleksiy Grechnyev on 5/7/2017.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>


#include "Navigator/Dijkstra/PointGraph.h"

namespace Navigator {
    namespace Dijkstra {

//============================================================================

        PointGraph::PointGraph(const std::string &fileName) : Graph({}) {
            using namespace std;
            using namespace Navigator::Math;

            ifstream in(fileName);

            if (!in)
                throw runtime_error("PointGraph: Cannot open file " + fileName);

            if (!parseFromStream(in))
                throw runtime_error("PointGraph: Cannot parse file " + fileName);

            in.close();
        }
//============================================================================

        PointGraph::PointGraph(const std::string &data, double rescale) : Graph({}) {
            using namespace std;
            using namespace Navigator::Math;

            stringstream in(data);

            // Read from stream
            if (!parseFromStream(in))
                throw runtime_error("PointGraph: Cannot parse string !");

            // Rescale
            for (Position3D &p : vertices) {
                p.x *= rescale;
                p.y *= rescale;
                p.z *= rescale;
            }
        }

//============================================================================
        double PointGraph::dijkstraP(int source, int destination, std::vector<Math::Position3D> &pointPath) {
            using namespace std;

            pointPath.clear();
            vector<int> path; // Path of vertex indices

            double result = dijkstra(source, destination, path);

            // Path to pointPath
            for (int i : path)
                pointPath.push_back(vertices[i]);  // Add vertex i

            return result;
        }
//============================================================================

        int PointGraph::findVertex(const Math::Position3D &coord) const {
            using namespace Navigator::Math;

            for (int i = 0; i < vertices.size(); ++i) {
                if (vertices[i].approx_equals(coord, 1.0e-10))
                    return i;
            }

            return -1; // Not found
        }

//============================================================================
        int PointGraph::findNearestVertex(const Math::Position3D &point) const {
            double bestDist = std::numeric_limits<double>::max(); // Best distance so far
            int bestInd = -1; // Index of the nearest found so far

            for (int i = 0; i < vertices.size(); ++i) {
                double dist = vertices[i].distance(point);
                if (dist < bestDist) {
                    bestDist = dist;
                    bestInd = i;
                }
            }

            return bestInd;
        }
//============================================================================

        void PointGraph::addEdge(int i, int j, double dist) {
            using namespace std;
            int size = edges.size();

            if (i < 0 || i >= size || j < 0 || j >= size)
                throw runtime_error("PointGraph::addEdge : index out of bounds.");

            vector<Edge> &ve = edges[i];  // Edges of vertex i

            // Check if the j-vertex exists already, I don't like stupid iterators
            for (Edge &e : ve)
                if (e.to == j) {
                    // Found !
                    e.weight = dist; // Replace the weight aka dist
                    return;
                }

            // Not found: add a new element
            ve.push_back(Edge(j, dist));
        }
//============================================================================

        bool PointGraph::parseFromStream(std::istream &in) {
            using namespace std;
            using namespace Navigator::Math;

            if (!in)
                return false;

            string line;

            // Check if a string is empty or blank (only spaces)
            auto isBlank = [](const string &s) -> bool {
                return s.empty() || s.find_first_not_of(" \r\n") == string::npos;
            };

            // Line 1 = type of file, ignoring blank lines
            for (;;) {
                getline(in, line);
                if (!isBlank(line))
                    break;
            }
//            cout << line << endl;

            // Note : ->GOOD file format :
            //
            // Vertices start with 0.
            // Edges can have directions. "1 2 107.0" does not mean "2 1 107.0"
            //
            // ->GRAPH file format (Alexey Roienko)
            //
            // Vertices start with 1.
            // Edges don't have directions. "1 2 107.0" automatically gives "2 1 107.0"

            bool flag;
            if (0 == line.find("->GOOD"))
                flag = true;
            else if (0 == line.find("->GRAPH"))
                flag = false;
            else {
                cerr << "Not ->GOOD or ->GRAPH !!!" << endl;
                cerr << "line = '" << line << "'" << endl;
                return false;
             }   

            // Read point positions
            double x, y;

            vertices.clear(); // Just in case

            while (true) {
                getline(in, line);
                stringstream stin(line);

                // Ignore blank lines
                if (isBlank(line))
                    continue;

                // Read x,y until an uncompatible line
                if (!(stin >> x >> y))
                    break;

                vertices.push_back(Position3D(x, y, 0.0));
//                cout << "(x, y) = " << x << " " << y << endl;
            }
//            cout << "vertices.size() = " << vertices.size() << endl;
            if (0 == vertices.size())
                return false;

//            cout << line << endl;

            if (0 != line.find("->EDGES")) {
                cerr << "Not ->EDGES !!!" << endl;
                cerr << line.find("->EDGES") << endl;
                cerr << "line = '" << line << "'" << endl;
                return false;
            }    

            // Read the edges
            int size = vertices.size();
            edges = vector<vector<Edge>>(size); // Create the vector of the correct size

            int i, j;
            double dist;

            while (in >> i >> j >> dist) {
                if (!flag) {
                    // change vertex index 1-based -> 0-based
                    --i;
                    --j;
                }

//                cout << i << " : " << j << " : " << dist << endl;
                addEdge(i, j, dist);
                if (!flag) {
                    addEdge(j, i, dist); // Add the other direction
                }
            }

            return true;
        }

//============================================================================

    }
}
