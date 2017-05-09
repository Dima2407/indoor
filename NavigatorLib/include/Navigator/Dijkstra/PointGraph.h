//
// Created by  Oleksiy Grechnyev on 5/7/2017.
//

#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "./Graph.h"
#include "Navigator/Math/Position3D.h"

namespace Navigator {
    namespace Dijkstra {
        /// Graph with Position3d coordinates of each vertex
        class PointGraph : public Graph{
        public: //========= Constructors ======
            /// Create from edges, vertices
            PointGraph(const std::vector<std::vector<Edge>> &edges, const std::vector<Math::Position3D> &vertices)
                    : Graph(edges), vertices(vertices) {
                if (edges.size() != vertices.size())
                    throw std::runtime_error("PointGraph: sizes of vertices and edges do not match.");
            }

            /// Create from file
            PointGraph(const std::string & fileName);

        public: //========= Methods ======
            /// A version of dijkstra which gives a vector of Position3D points
            double dijkstraP(int source, int destination, std::vector<Math::Position3D> &pointPath);
            
            // Get vertices
            const std::vector<Math::Position3D>  & getVertices() const{
                return vertices;
            }

        private: //========= Fields
            /// Vertices of the graph
            std::vector<Math::Position3D> vertices;
        };
    }
}

