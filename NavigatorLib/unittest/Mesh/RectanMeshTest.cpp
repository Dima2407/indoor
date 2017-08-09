//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#include <vector>

#include "RectanMeshTest.h"

namespace NaviTest {
    namespace Mesh {
        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(RectanMeshTest);

//===========================================
        void RectanMeshTest::test1() {
            using namespace Navigator::Mesh;
            using namespace Navigator::Math;

            constexpr double accuracy = 1.0e-10; // Accuracy

            // Create a simple rect mesh
            // x -coords: 1, 3, 5, 7, 9
            // y -coords: 1, 4, 7, 10

            RectanMesh mesh(5, 4, 2.0, 3.0, 1.0, 1.0);

            // Note that z-coordinate should not change
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(5.9, 5.6, 0.19)),
                                   Position3D(5.0, 7.0, 0.19), accuracy));

            // Slightly different values
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(6.1, 5.4, -0.91)),
                                   Position3D(7.0, 4.0, -0.91), accuracy));

            // Check more points
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(1.9, 2.4, 0.0)),
                                   Position3D(1.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(8.1, 8.6, 0.0)),
                                   Position3D(9.0, 10.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(5.9, 8.55, 0.0)),
                                   Position3D(5.0, 10.0, 0.0), accuracy));

            // Now let's try boundaries: corners
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(-100.0, -200.0, 0.0)),
                                   Position3D(1.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(100.0, -200.0, 0.0)),
                                   Position3D(9.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(-100.0, 200.0, 0.0)),
                                   Position3D(1.0, 10.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(100.0, 200.0, 0.0)),
                                   Position3D(9.0, 10.0, 0.0), accuracy));

            // Now boundaries: sides
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(-100.0, 8.4, 0.0)),
                                   Position3D(1.0, 7.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(100.0, 8.6, 0.0)),
                                   Position3D(9.0, 10.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(1.9, -20.5, 0.0)),
                                   Position3D(1.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(2.1, 20.5, 0.0)),
                                   Position3D(3.0, 10.0, 0.0), accuracy));
        }
//===========================================


        void RectanMeshTest::testMask() {
            using namespace std;
            using namespace Navigator::Mesh;
            using namespace Navigator::Math;

            constexpr double accuracy = 1.0e-10; // Accuracy

            // Create a simple rect mesh
            // x -coords: 1, 3, 5, 7, 9
            // y -coords: 1, 4, 7, 10
            RectanMesh mesh(5, 4, 2.0, 3.0, 1.0, 1.0);

            // Create a mask table
            vector<int> mTable(20);

            // Fill the table with the "identity" operation
            for (int i = 0; i < 20; i++)
                mTable[i] = i;

            // Make a few changes: exclude nodes 6, 10, 14
            mTable[6] = 2;
            mTable[10] = 9;
            mTable[14] = 18;

            // Load the table into the mesh
            mesh.setMaskTable(mTable);

            // Now check the node-6 zone
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(3.9, 5.6, 0.0)),
                                   Position3D(1.0, 7.0, 0.0), accuracy));
            //node-10 zone
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(5.9, 8.4, 0.0)),
                                   Position3D(5.0, 4.0, 0.0), accuracy));
            //node-14 zone
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(6.1, 8.4, 0.0)),
                                   Position3D(9.0, 7.0, 0.0), accuracy));

            // Check that other positions (outside the 3 zones) work as before

            // Note that z-coordinate should not change
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(5.9, 5.4, 0.19)),
                                   Position3D(5.0, 4.0, 0.19), accuracy));

            // Slightly different values
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(6.1, 5.4, -0.91)),
                                   Position3D(7.0, 4.0, -0.91), accuracy));

            // Check more points
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(1.9, 2.4, 0.0)),
                                   Position3D(1.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(8.1, 8.6, 0.0)),
                                   Position3D(9.0, 10.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(5.9, 8.55, 0.0)),
                                   Position3D(5.0, 10.0, 0.0), accuracy));

            // Now let's try boundaries: corners
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(-100.0, -200.0, 0.0)),
                                   Position3D(1.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(100.0, -200.0, 0.0)),
                                   Position3D(9.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(-100.0, 200.0, 0.0)),
                                   Position3D(1.0, 10.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(100.0, 200.0, 0.0)),
                                   Position3D(9.0, 10.0, 0.0), accuracy));

            // Now boundaries: sides
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(-100.0, 8.4, 0.0)),
                                   Position3D(1.0, 7.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(100.0, 8.6, 0.0)),
                                   Position3D(9.0, 10.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(1.9, -20.5, 0.0)),
                                   Position3D(1.0, 1.0, 0.0), accuracy));
            CPPUNIT_ASSERT(myPosEq(mesh.process(Position3D(2.1, 20.5, 0.0)),
                                   Position3D(3.0, 10.0, 0.0), accuracy));

        }

//===========================================
        void RectanMeshTest::setUp() {
            using namespace std;
            using namespace Navigator::Mesh;
            // Create a simple 5x4 rect mesh
            constexpr double nx = 5, ny = 4;
            constexpr double dx = 1.0, dy = 1.0;
            constexpr double x0 = 2, y0 = 2;

            rMesh = std::make_unique<RectanMesh>(nx, ny, dx, dy, x0, y0);
            // Create a mask table : 20 = nx*ny = 5*4
            vector<int> mTable(nx * ny);
            // Fill the table with the "identity" operation
            for (int i = 0; i < nx * ny; i++)
                mTable[i] = i;
            //black nodes
            mTable[6] = 7;
            mTable[10] = 11;
            mTable[14] = 18;

            rMesh->setMaskTable(mTable);
        }
//===========================================

        void RectanMeshTest::testCheckBlack() {
            // if point black
            CPPUNIT_ASSERT(rMesh->checkBlack(3, 4));
            CPPUNIT_ASSERT(rMesh->checkBlack(4, 4));
            CPPUNIT_ASSERT(rMesh->checkBlack(5, 4));
            // if point black (double)
            CPPUNIT_ASSERT(rMesh->checkBlack(3.4, 4.4));
            CPPUNIT_ASSERT(rMesh->checkBlack(4.4, 4.4));
            CPPUNIT_ASSERT(rMesh->checkBlack(5.4, 4.4));
            // if point white
            CPPUNIT_ASSERT(!rMesh->checkBlack(3, 3));
            CPPUNIT_ASSERT(!rMesh->checkBlack(4, 3));
            CPPUNIT_ASSERT(!rMesh->checkBlack(5, 3));
            // if point white (double)
            CPPUNIT_ASSERT(!rMesh->checkBlack(3.4, 3.4));
            CPPUNIT_ASSERT(!rMesh->checkBlack(4.4, 3.4));
            CPPUNIT_ASSERT(!rMesh->checkBlack(5.4, 3.4));
        }
//===========================================
        void RectanMeshTest::testCheckWall() {
            /// True if the line (x0,y0) -> (x,y) crosses a wall (obstacle)
            CPPUNIT_ASSERT(!rMesh->checkWall(2.4, 2.6, 5.99, 2.6));
            CPPUNIT_ASSERT(!rMesh->checkWall(2.6, 2.7, 3.5, 3.4));
            CPPUNIT_ASSERT(rMesh->checkWall(2.2, 2.7, 2.5, 4.3));
            CPPUNIT_ASSERT(!rMesh->checkWall(3.1, 3.2, 5.99, 3.6));
            CPPUNIT_ASSERT(rMesh->checkWall(3.4, 3.3, 3.2, 5.4));
        }
//===========================================


    }
}