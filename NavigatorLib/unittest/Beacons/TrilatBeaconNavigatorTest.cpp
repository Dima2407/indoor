//
// Created by  Oleksiy Grechnyev on 3/20/2017.
//

#include <memory>
#include <cmath>

#include "../mydoubleeq.h"

#include "Navigator.h"

#include "./TrilatBeaconNavigatorTest.h"


namespace NaviTest {
    namespace Beacons {

        // Register this suite !
        CPPUNIT_TEST_SUITE_REGISTRATION(TrilatBeaconNavigatorTest);

        //Create a fake RSSI
        double TrilatBeaconNavigatorTest::fakeRSSI(const Navigator::Math::Position3D &p1, const Navigator::Math::Position3D &p2, double txPower, double damp)
        {
            /*double dist = p1.distance(p2);
            double temp = log10(dist);
            return txPower - 10 * damp * temp;*/
            return txPower - 10 * damp * log10( p1.distance(p2) );
        }

        void TrilatBeaconNavigatorTest::testSimple() {
            using namespace std;
            using namespace Navigator::Beacons;
            using namespace Navigator::Math;
            using namespace Navigator::Math::Filter;

            // Set the accuracy
            constexpr double accuracy = 1.0e-10;

            // Let's add some beacons

            Beacon beacons[] = {
                    Beacon(BeaconUID("Rat", 13, 0), -3.7, 2.0, Position3D(0.1, 0.2, 0.0), ""),
                    Beacon(BeaconUID("Rat", 13, 1), -4.0, 2.5, Position3D(9.8, 0.3, 0.0), ""),
                    Beacon(BeaconUID("Rat", 13, 2), -100.8, 10.0, Position3D(-19, 100500, 189.0), "")
            };

            navigator1->addBeacons(beacons);

            // This shoud replace the beacon with UID  BeaconUID("Rat", 13, 2)
            beacons[2] = Beacon(BeaconUID("Rat", 13, 2), -5.8, 3.0, Position3D(-0.1, 10.7, 0.0), "");
            navigator1->addBeacon(beacons[2]);

            Position3D pos; // The outut position

            Position3D inPos(0.39, 0.23, 0.0); // Some input position

            pos = navigator1->process(BeaconReceivedData(
                    0.1, BeaconUID("Rat", 13, 0),
                    fakeRSSI(inPos, beacons[0].getPos(), beacons[0].getTxPower(), beacons[0].getDamp())
            ));
            CPPUNIT_ASSERT(isnan(pos.x) && isnan(pos.y) && isnan(pos.z));

            pos = navigator1->process(BeaconReceivedData(
                    0.2, BeaconUID("Rat", 13, 1),
                    fakeRSSI(inPos, beacons[1].getPos(), beacons[1].getTxPower(), beacons[1].getDamp())
            ));
            CPPUNIT_ASSERT(isnan(pos.x) && isnan(pos.y) && isnan(pos.z));

            pos = navigator1->process(BeaconReceivedData(
                    0.3, BeaconUID("Rat", 13, 2),
                    fakeRSSI(inPos, beacons[2].getPos(), beacons[2].getTxPower(), beacons[2].getDamp())
            ));
            CPPUNIT_ASSERT(myDoubleEq(pos.x, inPos.x, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(pos.y, inPos.y, accuracy));
            CPPUNIT_ASSERT(myDoubleEq(pos.z, inPos.z, accuracy));

            // Remove all data
            navigator1->clear();

            //------------------------------------
            // And go again with all new beacons
            const Beacon beacons2[] = {
                    Beacon(BeaconUID("Squirrel", 11, 0), -3.7, 2.0, Position3D(0.1, 0.2, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 1), -8.2, 2.5, Position3D(1.1, 0.1, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 2), -11.0, 1.5, Position3D(-0.1, 0.9, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 3), -5.8, 3.2, Position3D(0.7, 0.4, 0.0), ""),
                    Beacon(BeaconUID("Squirrel", 11, 4), -6.7, 2.9, Position3D(0.4, 0.7, 0.0), ""),
            };

            navigator1 -> addBeacons(beacons2);

            inPos = Position3D(0.46, 0.69, 0.0);

            for (int i = 0; i < 5; i++) {

                double timeStamp = 0.1 * i;

                const Beacon &b = beacons2[i];
                double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());

                BeaconUID uid = BeaconUID("Squirrel", 11, i);
                BeaconReceivedData brd(timeStamp, uid, rssi);

                // Process it and get a position
                pos = navigator1->process(brd);

                if (i < 2) {
                    // Expected : nan
                    CPPUNIT_ASSERT(isnan(pos.x) && isnan(pos.y) && isnan(pos.z));
                } else {
                    // Expected : inPos

                    CPPUNIT_ASSERT(myDoubleEq(pos.x, inPos.x, accuracy));
                    CPPUNIT_ASSERT(myDoubleEq(pos.y, inPos.y, accuracy));
                    CPPUNIT_ASSERT(myDoubleEq(pos.z, inPos.z, accuracy));
                }

            }

        }

        void TrilatBeaconNavigatorTest::setUp() {
            using namespace Navigator::Beacons;
            using namespace Navigator::Beacons::Factory;

            // Use NoFilter + NoFilter
            navigator1 = new TrilatBeaconNavigator(
                    std::make_shared<NoFilterFactory>(),
                    std::make_shared<NoFilterFactory>()
            );
        }

        void TrilatBeaconNavigatorTest::tearDown() {
            delete navigator1;
        }
    }
}