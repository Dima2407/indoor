//
// Created by  Oleksiy Grechnyev on 5/7/2017.
//
#include <iostream>
#include <fstream>


#include "Navigator/Dijkstra/PointGraph.h"

namespace Navigator {
    namespace Dijkstra {

//============================================================================

        PointGraph::PointGraph(const std::string &fileName) : Graph({}) {
            using namespace std;

            ifstream in(fileName);

            if (!in)
                throw runtime_error("PointGraph: Cannot open file" + fileName);

            string line;

            // Line 1 = type of file
            getline(in, line);
            bool flag;
            if (line == "->GOOD")
                flag = true;
            else if (line == "->GRAPH")
                flag = false;
            else
                throw runtime_error("PointGraph: Cannot parse file" + fileName);

            // Read point positions


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

    }
}