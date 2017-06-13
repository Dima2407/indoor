//
// Created by Igor Maschikevich on 6/13/2017.
//
#include "AlgorithmZUPTTest.h"




namespace AlgorithmZUPTTest{

}



/*
#include <vector>

#include "RectanMeshTest.h"

namespace NaviTest {
    namespace Mesh {
        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(RectanMeshTest);

        //----------------
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
        //----------------

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
            for (int i=0; i<20; i++)
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
        //----------------

    }
}*/
