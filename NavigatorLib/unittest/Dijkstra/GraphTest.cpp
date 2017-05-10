//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#include <vector>

#include "Navigator.h"

#include "GraphTest.h"

namespace NaviTest {
    namespace Dijkstra {

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
                             {Edge(5, 9.0)},                                              // 6
                             vector<Edge>()                                               // 7 (unconnected)
                     });
            vector<int> path;

            using vi = vector<int>;

            // Test various paths
            CPPUNIT_ASSERT( g1.dijkstra(0, 0, path) == 0.0) ;
            CPPUNIT_ASSERT( path == (vi{0}));

            CPPUNIT_ASSERT( g1.dijkstra(0, 4, path) == 6.0) ;
            CPPUNIT_ASSERT( path == (vi{0, 2, 3, 4}));
            CPPUNIT_ASSERT( g1.dijkstra(4, 0, path) == 6.0) ;
            CPPUNIT_ASSERT( path == (vi{4, 3, 2, 0}));

            CPPUNIT_ASSERT( g1.dijkstra(2, 4, path) == 4.0) ;
            CPPUNIT_ASSERT( path == (vi{2, 3, 4}));
            CPPUNIT_ASSERT( g1.dijkstra(4, 2, path) == 4.0) ;
            CPPUNIT_ASSERT( path == (vi{4, 3, 2}));

            CPPUNIT_ASSERT( g1.dijkstra(0, 6, path) == 17.0);
            CPPUNIT_ASSERT( path == (vi{0, 2, 3, 5, 6}));
            CPPUNIT_ASSERT( g1.dijkstra(6, 0, path) == 17.0);
            CPPUNIT_ASSERT( path == (vi{6, 5, 3, 2, 0}));

            CPPUNIT_ASSERT( g1.dijkstra(1, 6, path) == 20.0);
            CPPUNIT_ASSERT( path == (vi{1, 0, 2, 3, 5, 6}));
            CPPUNIT_ASSERT( g1.dijkstra(6, 1, path) == 20.0);
            CPPUNIT_ASSERT( path == (vi{6, 5, 3, 2, 0, 1}));

            CPPUNIT_ASSERT( isnan(g1.dijkstra(0, 7, path)) );
//            CPPUNIT_ASSERT( path.empty());

            cout << "path = ";
            for (int i : path)
                cout << i << " ";
            cout << endl;
        }
    }
}