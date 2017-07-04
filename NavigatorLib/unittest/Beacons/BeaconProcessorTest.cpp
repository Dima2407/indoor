//
// Created by  Oleksiy Grechnyev on 3/20/2017.
//

#include <memory>


#include "../mydoubleeq.h"

#include "Navigator.h"

#include "./BeaconProcessorTest.h"

namespace NaviTest {
    namespace Beacons {

        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(BeaconProcessorTest);

        void BeaconProcessorTest::testNoNo() {
            using namespace std;
            using namespace Navigator::Beacons;
            using namespace Navigator::Math;
            using namespace Navigator::Math::Filter;

            // Create a beacon processor with NoFilter + NoFilter
            Beacon b(BeaconUID("Turtle"), -4.0, 3.0, Position3D(0.1, 0.2, 0.0));
            BeaconProcessor bp(b, make_shared<NoFilter>(), make_shared<NoFilter>());

            // Set the accuracy
            constexpr double accuracy = 1.0e-10;
            // Now process some data
            double dist;

            dist = bp.process(-34.0, 0.1);
            CPPUNIT_ASSERT(myDoubleEq(dist, 10.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastDistance(), 10.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastTimeStamp(), 0.1, accuracy));

            dist = bp.process(-4.0, 0.2);
            CPPUNIT_ASSERT(myDoubleEq(dist, 1.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastDistance(), 1.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastTimeStamp(), 0.2, accuracy));

            dist = bp.process(-64.0, 0.3);
            CPPUNIT_ASSERT(myDoubleEq(dist, 100.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastDistance(), 100.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastTimeStamp(), 0.3, accuracy));

            // Reset and do it again
            bp.reset();


            dist = bp.process(-34.0, 0.1);
            CPPUNIT_ASSERT(myDoubleEq(dist, 10.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastDistance(), 10.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastTimeStamp(), 0.1, accuracy));

            dist = bp.process(-4.0, 0.2);
            CPPUNIT_ASSERT(myDoubleEq(dist, 1.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastDistance(), 1.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastTimeStamp(), 0.2, accuracy));

            dist = bp.process(-64.0, 0.3);
            CPPUNIT_ASSERT(myDoubleEq(dist, 100.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastDistance(), 100.0, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(bp.getLastTimeStamp(), 0.3, accuracy));

        }
    }
}
