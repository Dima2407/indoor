//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#pragma once

#include <vector>

#include "Edge.h"

namespace Navigator {
    namespace Dijkstra {
        /// Graph for Dijkstra algrithm
        class Graph {
        public: //========= Constructors ======
            // Create from a vector, noc checks
            Graph(const std::vector<std::vector<Edge>> &edges) :
                    edges(edges){}

            public: //========= Methods ============
            double dijkstra(int source, int destination, std::vector<int> & path);
        public: //=============data=============
            std::vector<std::vector<Edge>> edges;
        };
    }
}

