//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#pragma once

#include <vector>

#include "Navigator/Math/Position3D.h"

namespace Navigator {
    namespace Mesh {
        /** @brief A class to operate rectangular mesh
         *
         * @startuml
         * class RectanMesh{
         *
         * }
         * note bottom
         * // A class to operate rectangular mesh //
         * // It finds the nearest mesh node to the given point //
         * // If a mask table is loaded, find the nearest white node to the given node //
         * endnote
         * @enduml
         */
        class RectanMesh {
        public: // ======= Constructor
            RectanMesh(const int nx, const int ny, const double dx, const double dy, const double x0, const double y0)
                    : nx(nx), ny(ny),
                      dx(dx), dy(dy),
                      x0(x0), y0(y0) {}

        public: // ======= Methods
            /** @brief Process position using a discrete mesh and a mask table
             *
             * First a nearest mesh node to inPos is found
             * Second, the nearest white mesh node to the node is found (only if the mask table is loaded)
             * z coordinate is unchanged at present
             *
             *
             * @param[in]    inPos    Input Position
             * @return                Output position (Nearest white mesh node to inPos)
             */
            Math::Position3D process(const Math::Position3D & inPos);

            /// , must be of size nx*ny to be of any use

            /** @brief Use this to set up the mask table
             *
             * The maskTable is the vector of size nx*ny representing the black-white mask
             * maskTable[ind] = Index of the white site nearest to ind,
             * where ind = ix*ny + iy
             *
             * @param[in] maskTable  The vector of size nx*ny
             */
            void setMaskTable(const std::vector<int> &maskTable) {
                RectanMesh::maskTable = maskTable;
            }

        private: // ======= Parameters

            /// Mesh size : X
            const int nx;
            /// Mesh size : Y
            const int ny;
            /// Mesh step : X
            const double dx;
            /// Mesh step : Y
            const double dy;
            /// Mesh origin: X
            const double x0;
            /// Mesh origin: Y
            const double y0;

        private: // ======= Mask table data

            /// The table of size nx*ny gives the index to the nearest white mesh node to the given node, ignored if empty
            std::vector<int> maskTable;

        };
    }
}


