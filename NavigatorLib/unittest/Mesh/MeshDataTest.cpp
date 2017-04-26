//
// Created by  Oleksiy Grechnyev on 4/26/2017.
//


#include "Navigator.h"

#include "../mydoubleeq.h"

#include "MeshDataTest.h"

namespace NaviTest {
    namespace Mesh {
        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(MeshDataTest);

        void MeshDataTest::test1() {
            using namespace Navigator::Mesh;

            // Create a mesh
            // x = -1, 2, 5, 8
            // y = -1, 1, 3, 5, 7
            MeshData mesh(4, 5, 3.0, 2.0, -1.0, -1.0);

            // Check the x -> ix conversionn (rounding)
            CPPUNIT_ASSERT(0 ==  mesh.x2ix(-100.3));
            CPPUNIT_ASSERT(0 ==  mesh.x2ix(-2.0));
            CPPUNIT_ASSERT(0 ==  mesh.x2ix(0.4));
            CPPUNIT_ASSERT(1  ==  mesh.x2ix(0.6));
            CPPUNIT_ASSERT(1  ==  mesh.x2ix(3.4));
            CPPUNIT_ASSERT(2  ==  mesh.x2ix(3.6));
            CPPUNIT_ASSERT(2  ==  mesh.x2ix(6.4));
            CPPUNIT_ASSERT(3 ==  mesh.x2ix(6.6));
            CPPUNIT_ASSERT(3 ==  mesh.x2ix(100.2));

            // Same for y
            CPPUNIT_ASSERT(0 ==  mesh.y2iy(-100.3));
            CPPUNIT_ASSERT(0 ==  mesh.y2iy(-0.1));
            CPPUNIT_ASSERT(1 ==  mesh.y2iy(0.1));
            CPPUNIT_ASSERT(1 ==  mesh.y2iy(1.9));
            CPPUNIT_ASSERT(2 ==  mesh.y2iy(2.1));
            CPPUNIT_ASSERT(2 ==  mesh.y2iy(3.9));
            CPPUNIT_ASSERT(3 ==  mesh.y2iy(4.1));
            CPPUNIT_ASSERT(3 ==  mesh.y2iy(5.9));
            CPPUNIT_ASSERT(4 ==  mesh.y2iy(6.1));
            CPPUNIT_ASSERT(4 ==  mesh.y2iy(100.2));

            // Check ix -> x
            const double acc = 1.0e-10;

            CPPUNIT_ASSERT(myDoubleEq(mesh.ix2x(0), -1.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.ix2x(1), 2.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.ix2x(2), 5.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.ix2x(3), 8.0, acc));

            //Same for y
            CPPUNIT_ASSERT(myDoubleEq(mesh.iy2y(0), -1.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.iy2y(1), 1.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.iy2y(2), 3.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.iy2y(3), 5.0, acc));
            CPPUNIT_ASSERT(myDoubleEq(mesh.iy2y(4), 7.0, acc));

        }
    }
}