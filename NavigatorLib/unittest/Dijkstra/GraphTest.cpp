//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#include <vector>

#include "Navigator.h"

#include "GraphTest.h"

namespace NaviTest {
    namespace Beacons {

        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(GraphTest);


        void GraphTest::testDijkstra() {
            using namespace std;
            using namespace Navigator::Dijkstra;

            // A simple test graph
            Graph g1({
                             {Edge(1, 3.0), Edge(2, 2.0)},                                // 0
                             {Edge(0, 3.0), Edge(4, 7.0)},                                // 1
                             {Edge(0, 2.0), Edge(3, 2.0), Edge(4, 5.0)},                  // 2
                             {Edge(2, 2.0), Edge(4, 2.0), Edge(5, 4.0)},                  // 3
                             {Edge(1, 7.0), Edge(2, 5.0), Edge(3, 2.0), Edge(5, 6.0)},    // 4
                             {Edge(3, 4.0), Edge(4, 6.0), Edge(6, 9.0)},                  // 5
                             {Edge(5, 9.0)}                                               // 6
                     });
            vector<int> path;

            CPPUNIT_ASSERT( g1.dijkstra(0, 0, path) == 0.0) ;
            CPPUNIT_ASSERT( g1.dijkstra(0, 4, path) == 6.0) ;

        }
    }
}