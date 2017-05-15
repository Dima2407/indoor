//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#pragma once

#include <vector>

#include "Navigator/Math/Position3D.h"
#include "./MeshData.h"

namespace Navigator {
    namespace Mesh {
        /** @brief A class to operate rectangular mesh defined by a MeshData object
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
        public: // ======= Constructors
            // Create a mesh with given parameters and no masktable
            RectanMesh(const int nx, const int ny, const double dx, const double dy, const double x0, const double y0)
                    : mesh(nx, ny, dx, dy, x0, y0) {}

           RectanMesh(const std::string &meshFileName, const std::string &maskTblFileName) : mesh(meshFileName) {
               using namespace std;

               int size = this -> size();
               vector<int> mTable(size);

               cout << "Reading mesh from file " << maskTblFileName << endl;
               ifstream in2(maskTblFileName);
               if (!in2) {
                   cerr << "Error: Cannot open file " << maskTblFileName << endl;
                   exit(1);
               }
               for (int i=0; i< size; i++) {
                   in2 >> mTable[i];
                   if (!in2) {
                       std::cerr << "Error reading data from file " << maskTblFileName << endl;
                       exit(1);
                   }
               }
               in2.close();

               // Load the table
               setMaskTable(mTable);
           }

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
            Math::Position3D process(const Math::Position3D & inPos) const;

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
            
            const std::vector<int> & getMaskTable() const {
                return maskTable;
            }

            const MeshData &getMesh() const {
                return mesh;
            }

            int size() const {
                return mesh.nx * mesh.ny;
            }
        private: // ======= Parameters

            MeshData mesh; // Mesh parameters


        private: // ======= Mask table data

            /// The table of size nx*ny gives the index to the nearest white mesh node to the given node, ignored if empty
            std::vector<int> maskTable;

        };
    }
}


