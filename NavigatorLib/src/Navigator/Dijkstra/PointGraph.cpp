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
//                cout << i << " : " << j << " : " << dist << endl;
                edges[i].push_back(Edge(j, dist));
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

    }
}