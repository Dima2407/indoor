//
// Created by  Oleksiy Grechnyev on 5/4/2017.
//


#include <random>
#include <ctime>
#include <iostream>
#include <cstdio>

#include "StandardBeaconNavigatorTest.h"

namespace NaviTest {
    namespace Beacons {

        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(StandardBeaconNavigatorTest);

        void StandardBeaconNavigatorTest::testInit() {
            using namespace std;
            using namespace Navigator::Beacons;
            using namespace Navigator::Beacons::Factory;
            using namespace Navigator::Math;
            using namespace Navigator::Math::Filter;

            // The idea is to create one standard navigator,
            // And two trilat navigators to emulate the "before" and "after" behavior

            StandardBeaconNavigator stNav(nullptr, false); // No mesh, Android

            // trNav1: The Init configuration
            TrilatBeaconNavigator trNav1(
                    make_shared<Factory::MovingAverageFilterFactory>(20),
                    make_shared<NoFilterFactory>()
            );

            trNav1.setUseNearest(3);

            // trNav2: The Android after-init config
            TrilatBeaconNavigator trNav2(
                    make_shared<Factory::MovingAverageFilterFactory>(3),
                    make_shared<NoFilterFactory>()
            );

            trNav2.setBeaconTimeout(1.5);
            trNav2.setUseNearest(3);

            // Now let's create some beacons and add them
            const Beacon beacons[] = {
                    Beacon(BeaconUID("Squirrel", 11, 0), -43.7, 2.0, Position3D(0.1, 0.2, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 1), -48.2, 2.5, Position3D(1.1, 0.1, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 2), -41.0, 1.8, Position3D(-0.1, 0.9, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 3), -45.8, 3.2, Position3D(0.7, 0.4, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 4), -46.7, 2.9, Position3D(0.4, 0.7, 0.0), ""),
            };
            stNav.addBeacons(beacons);
            trNav1.addBeacons(beacons);
            trNav2.addBeacons(beacons);

            // Now let's put some random RSSIs
            // Seed with time the old-fashioned way
            mt19937 randomEngine(time(nullptr));

            // RSSI is random between -90 and -50
            uniform_real_distribution<double> randRssiDist(-90.0, -50.0);

            constexpr int NUM_RSSI = 20;

            // Generate packets with random RSSI in range
            vector<vector<BeaconReceivedData>> data(NUM_RSSI);

            // Loop over timestamps
            for (int i = 0; i < NUM_RSSI; ++i) {
                double ts = 0.44 * i;
                // Loop over beacons
                for (int j = 0; j < 5; ++j) {
                    double rssi = randRssiDist(randomEngine);
                    data[i].push_back(BeaconReceivedData(ts, BeaconUID("Squirrel", 11, j), rssi));
                }
            }


            // Now process data through 3 navigators
            Position3D pos, pos1, pos2;

//            puts("");
            for (const auto & brds : data) {
                pos = stNav.process(brds);
                pos1 = trNav1.process(brds);
                pos2 = trNav2.process(brds);

                double ts = brds[0].timestamp;

                // Before and after init
                if (stNav.isInitFinished()) {
                    CPPUNIT_ASSERT(pos == pos2);
                } else {
                    CPPUNIT_ASSERT(pos == pos1);
                }
                printf(" %f  :  %f %f  :  %f %f  :  %f %f \n", ts,  pos.x, pos.y,  pos1.x, pos1.y,  pos2.x, pos2.y);
            }
        }
    }
}