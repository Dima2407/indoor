//
// Created by  Oleksiy Grechnyev on 5/7/2017.
//
#include <iostream>
#include <fstream>
#include <sstream>


#include "Navigator/Dijkstra/PointGraph.h"

namespace Navigator {
    namespace Dijkstra {

//============================================================================

        PointGraph::PointGraph(const std::string &fileName) : Graph({}) {
            using namespace std;
            using namespace Navigator::Math;

            ifstream in(fileName);

            if (!in)
                throw runtime_error("PointGraph: Cannot open file" + fileName);

            string line;

            // Line 1 = type of file
            getline(in, line);
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
            if (line == "->GOOD")
                flag = true;
            else if (line == "->GRAPH")
                flag = false;
            else
                throw runtime_error("PointGraph: Cannot parse file" + fileName);

            // Read point positions
            double x, y;

            while (true) {
                getline(in, line);
                stringstream stin(line);

                // Read x,y until an uncompatible line
                if (! (stin >> x >> y))
                    break;

                vertices.push_back(Position3D(x, y, 0.0));
//                cout << "(x, y) = " << x << " " << y << endl;
            }
//            cout << "vertices.size() = " << vertices.size() << endl;
            if (0 == vertices.size())
                throw runtime_error("PointGraph: Cannot parse file" + fileName);

//            cout << line << endl;

            if (line != "->EDGES")
                throw runtime_error("PointGraph: Cannot parse file" + fileName);

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

            in.close();
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

        int PointGraph::findVertex(const Math::Position3D &coord) const{
            using namespace Navigator::Math;

            for (int i = 0; i < vertices.size(); ++i) {
                if (vertices[i].approx_equals(coord, 1.0e-10))
                    return i;
            }

            return -1; // Not found
        }
//============================================================================

        void PointGraph::addEdge(int i, int j, double dist) {
            using namespace std;
            int size = edges.size();

            if (i < 0 || i >= size || j < 0 || j >= size)
                throw runtime_error("PointGraph::addEdge : index out of bounds.");

            vector<Edge> & ve = edges[i];  // Edges of vertex i

            // Check if the j-vertex exists already, I don't like stupid iterators
            for (Edge & e : ve)
                if (e.to == j) {
                    // Found !
                    e.weight = dist; // Replace the weight aka dist
                    return;
                }

            // Not found: add a new element
            ve.push_back(Edge(j, dist));
        }
//============================================================================

    }
}