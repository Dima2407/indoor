//
// Created by  Oleksiy Grechnyev on 5/7/2017.
//

#include <vector>
#include <iostream>

#include "Navigator.h"

#include "PointGraphTest.h"

namespace NaviTest {
    namespace Dijkstra {

        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(PointGraphTest);

        void PointGraphTest::test1() {

            using namespace std;
            using namespace Navigator::Dijkstra;
            using namespace Navigator::Math;

            // A simple test graph
            // Edges
            const vector<vector<Edge>> edges = {
                    {Edge(1, 3.0), Edge(2, 2.0)},                                // 0
                    {Edge(0, 3.0), Edge(4, 7.0)},                                // 1
                    {Edge(0, 2.0), Edge(3, 2.0), Edge(4, 5.0)},                  // 2
                    {Edge(2, 2.0), Edge(4, 2.0), Edge(5, 4.0)},                  // 3
                    {Edge(1, 7.0), Edge(2, 5.0), Edge(3, 2.0), Edge(5, 6.0)},    // 4
                    {Edge(3, 4.0), Edge(4, 6.0), Edge(6, 9.0)},                  // 5
                    {Edge(5, 9.0)},                                              // 6
                    vector<Edge>()                                               // 7 (unconnected)
            };

            // Let's give it some vertices
            const vector<Position3D> v = {
                    {1.0, 0.0, 0.0}, // 0
                    {0.0, 2.0, 0.0}, // 1
                    {3.0, 0.0, 0.0}, // 2
                    {5.0, 0.0, 0.0}, // 3
                    {7.0, 0.0, 0.0}, // 4
                    {8.0, 3.0, 0.0}, // 5
                    {17.0, 3.0, 0.0}, // 6
                    {17.0, 10.0, 0.0} // 7
            };

            PointGraph g(edges, v);

            // Test findVertex() :
            CPPUNIT_ASSERT(g.findVertex(Position3D(5.0, 0.0, 0.0)) == 3 );
            CPPUNIT_ASSERT(g.findVertex(Position3D(5.01, 0.0, 0.0)) == -1 );
            CPPUNIT_ASSERT(g.findVertex(Position3D(17.0, 3.0, 0.0)) == 6 );
            CPPUNIT_ASSERT(g.findVertex(Position3D(17.0, 3.01, 0.0)) == -1 );

            // Test findNearestVertex() :
            CPPUNIT_ASSERT(g.findNearestVertex(Position3D(5.0, 0.0, 0.0)) == 3 );
            CPPUNIT_ASSERT(g.findNearestVertex(Position3D(5.99, -1.7, 0.0)) == 3 );
            CPPUNIT_ASSERT(g.findNearestVertex(Position3D(6.01, -1.7, 0.0)) == 4 );
            CPPUNIT_ASSERT(g.findNearestVertex(Position3D(15.0, 6.49, 0.0)) == 6 );
            CPPUNIT_ASSERT(g.findNearestVertex(Position3D(15.0, 6.51, 0.0)) == 7 );

            // Test a path
            using vi = vector<int>;
            vector<int> path;
            vector<Position3D> pointPath;

            // Normal path first, dijkstra inherited from Graph
            CPPUNIT_ASSERT( g.dijkstra(1, 6, path) == 20.0);
            CPPUNIT_ASSERT( path == (vi{1, 0, 2, 3, 5, 6}));

            // And now dijkstraP and the point path
            const vector<Position3D> expected = {v[1], v[0], v[2], v[3], v[5], v[6]};

            CPPUNIT_ASSERT( g.dijkstraP(1, 6, pointPath) == 20.0);
            CPPUNIT_ASSERT( pointPath == expected);

        }
    }
}