//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#pragma once

#include <vector>

#include "Edge.h"

namespace Navigator {
    namespace Dijkstra {
        /// Graph for the Dijkstra algorithm
        class Graph {
        public: //========= Constructors ======
            // Create from a vector, no checks
            Graph(const std::vector<std::vector<Edge>> &edges) :
                    edges(edges) {}
                    
            // Get number of vertices
            int getSize() const {
                return edges.size();
            }
            
            // Get edges
            const std::vector<std::vector<Edge>> & getEdges() const {
                return edges;
            }

        public: //========= Methods ============
            /** @brief  Find the shortest path between source and destination with Dijkstra
             *
             * Vertex indices start with 0 !
             * throws runtime_error if index out of range
             *
             * @param[in]   source
             * @param[in]   destination
             * @param[out]  path (empty vector if not found)
             * @return      Shortest distance or nan
             */
            virtual double dijkstra(int source, int destination, std::vector<int> &path);

        protected: //=============data=============
            /// Edges connected to each vertex
            std::vector<std::vector<Edge>> edges;
        };
    }
}

