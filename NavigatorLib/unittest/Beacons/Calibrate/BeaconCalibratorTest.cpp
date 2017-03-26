//
// Created by  Oleksiy Grechnyev on 3/26/2017.
//

#include "Navigator.h"

#include "../../mydoubleeq.h"

#include "BeaconCalibratorTest.h"

namespace NaviTest {
    namespace Beacons {
        namespace Calibrate {

            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(BeaconCalibratorTest);

            void BeaconCalibratorTest::testCalibrate() {
                using namespace std;
                using namespace Navigator::Beacons;
                using namespace Navigator::Beacons::Calibrate;
                using namespace Navigator::Math::Trilat;
                using Navigator::Math::Position3D;

                // Beacons
                const Position3D beaconPositions[] = {
                        Position3D(0.02, 0.02, 0.0),
                        Position3D(2.96, 0.03, 0.0),
                        Position3D(0.01, 2.97, 0.0),
                        Position3D(2.95, 2.91, 0.0),
                        Position3D(12.6, 17.8, 0.0),
                };
                const Beacon beacons[] = {
                        Beacon(BeaconUID("ABC", 1, 0), nan(""), nan(""), beaconPositions[0], ""),
                        Beacon(BeaconUID("ABC", 1, 1), nan(""), nan(""), beaconPositions[1], ""),
                        Beacon(BeaconUID("ABC", 1, 2), nan(""), nan(""), beaconPositions[2], ""),
                        Beacon(BeaconUID("ABC", 1, 3), nan(""), nan(""), beaconPositions[3], ""),
                        Beacon(BeaconUID("ABC", 1, 4), nan(""), nan(""), beaconPositions[4], "")
                };

                // Create the calibrator
                BeaconCalibrator calibrator;
                // Add beacons to the calibrator
                calibrator.addBeacons(beacons);

                // We calibrate at several points
                const Position3D points[] = {
                        Position3D(1.3, 0.8, 0.0),
                        Position3D(2.4, 0.7, 0.0),
                        Position3D(0.6, 2.2, 0.0),
                        Position3D(2.1, 2.0, 0.0),
                };

                // Create the vector of calibration points
                vector<CalibrationPoint> calPoints(4);

                // Data for fake RSSI's for this example.
                const double fakeTxPower[] = {-35.0, -45.0, -40.0, -50.0, -30.0};
                const double fakeDamp[] = {2.2, 1.8, 2.3, 2.8, 3.2};

                // Loop over 4 calibration points
                for (int pointInd = 0; pointInd < 4; ++pointInd) {
                    calPoints[pointInd].position = points[pointInd]; // Set the position
                    // Add fake events from each beacon
                    for (int beacInd = 0; beacInd < 5; ++beacInd) {
                        // simulated noise
                        for (int noiseInd = -5; noiseInd <= +5; noiseInd++) {
                            double noise = noiseInd * 0.5;

                            const double timeStamp = 0.0;
                            BeaconUID uid("ABC", 1, beacInd);
                            // Fake rssi + noise
                            double rssi = noise + fakeRSSI(points[pointInd], beaconPositions[beacInd],
                                                           fakeTxPower[beacInd], fakeDamp[beacInd]);

                            // Add data packet
                            calPoints[pointInd].packets.push_back(
                                    BeaconReceivedData(timeStamp, uid, rssi)
                            );
                        }
                    }
                }
                // Do the actual calibration
                CalibrationConfig config(5.0, -3.074, -72.88, -70.0);
                const auto & result = calibrator.calibrate(calPoints, config);

                constexpr double accuracy = 1.0e-10;

                // Check the results
                for (int beacInd = 0; beacInd < 5; ++beacInd) {
                    BeaconUID uid("ABC", 1, beacInd);
                    const Beacon &beacon = result.at(uid);

                    if (beacInd < 4) {
                        CPPUNIT_ASSERT(myDoubleEq(beacon.getTxPower(), fakeTxPower[beacInd], accuracy));
                        CPPUNIT_ASSERT(myDoubleEq(beacon.getDamp(), fakeDamp[beacInd], accuracy));
                        CPPUNIT_ASSERT(beacon.isCalibrated());
                    } else { // Beacon 4 is NOT calibrated
                        CPPUNIT_ASSERT(isnan(beacon.getTxPower()) && isnan(beacon.getDamp()));
                        CPPUNIT_ASSERT(!beacon.isCalibrated());
                    }
                }
            }
//================================================================================

            void BeaconCalibratorTest::testCalibrate1p() {
                using namespace std;
                using namespace Navigator::Beacons;
                using namespace Navigator::Beacons::Calibrate;
                using namespace Navigator::Math::Trilat;
                using Navigator::Math::Position3D;

                BeaconUID uid("Rat");

                vector<CalibrationPoint> calPoints(1);

                Position3D bPos(1.2, 2.3, 0.0); // Beacon position
                Position3D cPos(3.7, 2.9, 0.0); // Calibration position

                // Create the calibrator
                BeaconCalibrator calibrator;
                Beacon beacon(uid, nan(""), nan(""), bPos, "");
                calibrator.addBeacon(beacon);

                double dist = bPos.distance(cPos);

                calPoints[0].position = cPos;
                calPoints[0].packets.push_back(
                        BeaconReceivedData(0.0, uid, fakeRSSI(dist, -70.0, 1.8))
                );

                // Normal 1-point calibration
                CalibrationConfig config(5.0, -3.074, -72.88, -70.0);
                const auto & result = calibrator.calibrate(calPoints, config);

                constexpr double accuracy = 1.0e-10;
                CPPUNIT_ASSERT(myDoubleEq(result.at(uid).getTxPower(), -70.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(result.at(uid).getDamp(), 1.8, accuracy));

                // Now we go just below the line of sight
                // Don't forget to reset the beacon
                calibrator.deleteBeacon(uid);
                calibrator.addBeacon(beacon);
                calPoints[0].packets[0] = BeaconReceivedData(0.0, uid, fakeRSSI(dist, -70.0, 2.7));
                calibrator.calibrate(calPoints, config);
                CPPUNIT_ASSERT(isnan(result.at(uid).getTxPower()) && isnan(result.at(uid).getDamp()));

                // Now check the 5-meter rule : distance 5.1m
                cPos = Position3D(6.3, 2.3, 0.0);
                dist = bPos.distance(cPos);
                calibrator.deleteBeacon(uid);
                calibrator.addBeacon(beacon);
                calPoints[0].position = cPos;
                calPoints[0].packets[0] = BeaconReceivedData(0.0, uid, fakeRSSI(dist, -40.0, 2.0));
                calibrator.calibrate(calPoints, config);
                CPPUNIT_ASSERT(isnan(result.at(uid).getTxPower()) && isnan(result.at(uid).getDamp()));
            }
//================================================================================

        }
    }
}