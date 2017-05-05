//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#pragma once

namespace Navigator {
    namespace Dijkstra {
        /// Edge of a graph
        struct Edge {
            /// Constructor
            Edge(int to, double weight) : to(to), weight(weight) {}

            /// Neighbor index
            int to;

            /// Weight (or distance) of the edge
            double weight;
        };
    }
}


