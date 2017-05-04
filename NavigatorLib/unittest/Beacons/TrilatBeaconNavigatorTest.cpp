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

//=============================================================================================================
        //Create a fake RSSI
        double TrilatBeaconNavigatorTest::fakeRSSI(const Navigator::Math::Position3D &p1,
                                                   const Navigator::Math::Position3D &p2, double txPower, double damp) {
            /*double dist = p1.distance(p2);
            double temp = log10(dist);
            return txPower - 10 * damp * temp;*/
            return txPower - 10 * damp * log10(p1.distance(p2));
        }
//=============================================================================================================

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

            Position3D pos; // The output position

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

            navigator1->addBeacons(beacons2);

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
//=============================================================================================================

        void TrilatBeaconNavigatorTest::setUp() {
            using namespace Navigator::Beacons;
            using namespace Navigator::Beacons::Factory;

            // Use NoFilter + NoFilter
            navigator1 = new TrilatBeaconNavigator(
                    std::make_shared<NoFilterFactory>(),
                    std::make_shared<NoFilterFactory>()
            );
        }
//=============================================================================================================

        void TrilatBeaconNavigatorTest::tearDown() {
            delete navigator1;
        }
//=============================================================================================================

        void TrilatBeaconNavigatorTest::testHistory() {
            using namespace std;
            using namespace Navigator::Beacons;
            using namespace Navigator::Beacons::Factory;
            using namespace Navigator::Math;
            using namespace Navigator::Math::Filter;


            const Beacon beacons[] = {
                    Beacon(BeaconUID("Rat", 13, 0), -30.7, 2.0, Position3D(0.1, 0.2, 0.0), ""),
                    Beacon(BeaconUID("Rat", 13, 1), -40.0, 2.5, Position3D(9.8, 0.3, 0.0), ""),
                    Beacon(BeaconUID("Rat", 13, 2), -50.8, 3.0, Position3D(-0.1, 10.7, 0.0), "")
            };

            navigator1->addBeacons(beacons);

            // Let's add some RSSI signals here
            vector<vector<BeaconReceivedData>> myHist(6);

            double stupidRSSI[][3] = {
                    {-55.1, -56.2, -57.3},
                    {-64.1, -66.2, -69.3},
                    {-75.1, -76.2, -77.3},
                    {-51.4, -52.0, -53.6},
                    {-61.4, -62.5, -63.6},
                    {-71.9, -72.8, -73.7}
            };

            for (int i=0; i<6; i++) {
                double timestamp = 0.45*i;

                for (int j=0; j<3; j++) {
                    myHist[i].push_back(BeaconReceivedData(timestamp, BeaconUID("Rat", 13, j), stupidRSSI[i][j]));
                }
            }

            CPPUNIT_ASSERT(navigator1 -> getHistory().empty());

            // Start recording history
            navigator1 -> startHistory();

            // Send packets to the Navigator
            for (auto const & brds : myHist)
                navigator1 -> process(brds);

            // Stop recording history
            navigator1 -> stopHistory();

            Position3D pos1, pos2;

            pos1 = navigator1 -> getLastPosition();
//            cout << "X = " << pos1.x << " Y = " << pos1.y << endl;

            // Check the history
            CPPUNIT_ASSERT(navigator1->getHistory() == myHist);

            // Re-run the history with new filters
            navigator1 -> rerunHistory(
                    std::make_shared<MovingAverageFilterFactory>(3),
                    std::make_shared<AlphaTrimmedFilterFactory>(6, 0.3)
            );

            pos1 = navigator1 -> getLastPosition(); // Get position after rerun

            // Create another navigator, string with identical funny filters
            // Run the same packets
            TrilatBeaconNavigator navi2(
                    std::make_shared<MovingAverageFilterFactory>(3),
                    std::make_shared<AlphaTrimmedFilterFactory>(6, 0.3)
            );

            navi2.addBeacons(beacons);

            for (auto const & brds : myHist)
                navi2.process(brds);

            pos2 = navi2.getLastPosition();

            // Check that positions coincide
            CPPUNIT_ASSERT(pos1 == pos2);
        }
    }
//=============================================================================================================

}