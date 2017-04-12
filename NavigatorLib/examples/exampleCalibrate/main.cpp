//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

// Beacon calibration example

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>


// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the librrary
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Calibrate;
using namespace Navigator::Beacons::Calibrate::Algorithm;
using namespace Navigator::Math::Trilat;
using Navigator::Math::Position3D;

/** @brief An example of Navigator usage with beacon calibration
 *
 * @return
 */
int main() {
    // What is calibration?
    // Calibration is the way to find txPower and damp of every beacon in the room
    //
    // How it is done ?
    //
    // We choose a few calibration points with known coordinates. I recommend at least 4 points.
    //
    //
    // In each point, we stand still with our device for a while (like 1 minute or something) to gather data
    // packets from different beacons. We save this data (position + packets)
    // in a CalibrationPoint structure a form an std::vector of such structure
    //
    //
    // Note that distances above max distance (typically 6 meters) are discarded
    // And so are weak RSSI signals (the line-of-sight question ),
    // see CalibrationConfig.h for details
    //
    // When calibrrating with at least 2 legitimate points (for a beacon)
    // It uses linear least squares
    // If only one point, it returns damp for the default txPower, it's bad
    //
    // In this example I simulate beacon data packets with fake RSSIs
    //
    // We also create a calibrator and give it positions of all beacons
    //
    // Finally we run the calibrator and get txPower and RSSI of each beacon

    //------------------------------------

    // 1) Create beacons and the calibrator
    //
    // Let's create some beacons around approx 3x3 square
    // In real life we get beacon positions from the server
    // Beacons are not calibrated yet, so let's put their txPower and damp to nan
    // Only beacon positions and UID are needed
    // The last one is too far away, will not be calibrated
    const Position3D beaconPositions[] = {
            Position3D(0.01, 0.03, 0.0),
            Position3D(2.97, 0.04, 0.0),
            Position3D(0.02, 2.96, 0.0),
            Position3D(2.94, 2.89, 0.0),
            Position3D(12.9, 17.9, 0.0),
    };


    const Beacon beacons[] = {
            Beacon(BeaconUID("Chipmunk", 1, 0), nan(""), nan(""), beaconPositions[0], ""),
            Beacon(BeaconUID("Chipmunk", 1, 1), nan(""), nan(""), beaconPositions[1], ""),
            Beacon(BeaconUID("Chipmunk", 1, 2), nan(""), nan(""), beaconPositions[2], ""),
            Beacon(BeaconUID("Chipmunk", 1, 3), nan(""), nan(""), beaconPositions[3], ""),
            Beacon(BeaconUID("Chipmunk", 1, 4), nan(""), nan(""), beaconPositions[4], "")
    };

    // Create the calibrator
    BeaconCalibrator calibrator;

    /* Add beacons to the calibrator
     *
     * You can add them one by one, or as an array/container
     * /
     *
    /*for (const Beacon &b : beacons)
        calibrator.addBeacon(b);*/
    calibrator.addBeacons(beacons);

    //------------------------------------

    // 2) Create points and the calibration points (point + events)
    // We calibrate at several points
    const Position3D points[] = {
            Position3D(1.2, 0.7, 0.0),
            Position3D(2.5, 0.9, 0.0),
            Position3D(0.8, 2.1, 0.0),
            Position3D(2.2, 1.9, 0.0),
    };

    // Create the vector of calibration points
    // Each calibration point includes position and a std::vector of beacon signals
    vector<CalibrationPoint> calPoints(4);

    // Now we create fake RSSI's for this example.
    // In real life you take RSSI from beacons at each calibration point
    // We have to define txPower and damp for the fake RSSI's
    // We want to reproduce them by calibration
    const double fakeTxPower[] = {-50.0, -55.0, -65.0, -60.0, -70.0};
    const double fakeDamp[] = {2.1, 1.7, 2.4, 2.7, 3.1};

    // Loop over 4 calibration points
    for (int pointInd = 0; pointInd < 4; ++pointInd) {
        calPoints[pointInd].position = points[pointInd]; // Set the position

        // Now add fake events from each beacon
        // In real life we add all real data packets for this calibration point
        // Loop over beacons
        for (int beacInd = 0; beacInd < 5; ++beacInd) {

            // We generate several packets for each point and beacon, with a simulated noise
            // Calibrator should simply average over it
            for (int noiseInd = -5; noiseInd <= +5; noiseInd++) {
                double noise = noiseInd * 0.5;

                // Timestamp is not used for calibration, we put 0.0
                const double timeStamp = 0.0;
                // The correct uid of the beacon
                BeaconUID uid("Chipmunk", 1, beacInd);
                // Fake rssi signal for given calibration point and beacon + noise
                double rssi = noise + fakeRSSI(points[pointInd], beaconPositions[beacInd],
                                               fakeTxPower[beacInd], fakeDamp[beacInd]);

                // Add data packet with uid and rssi
                calPoints[pointInd].packets.push_back(
                        BeaconReceivedData(timeStamp, uid, rssi)
                );
            }

        }
    }

    //------------------------------------
    // 3) Create configuration and do the actual calibration

    // Create the config
    // See other parameters in CalibrationConfig.h
//    CalibrationConfig config(6.0, -2.021, -74.21, -70.0, 2.2);
    CalibrationConfig config;  // Default config

    // Run the calibration finally
    const auto &result = calibrator.calibrate(calPoints, config);

    // Print the result
    // The result is a std::unordered_map<BeaconUID, Beacon>

    cout << "All beacons : " << endl;

    for (const auto &val : result) {
        // Result is a std::pair<BeaconUID, Beacon>
        const BeaconUID &uid = val.first;
        const Beacon &beacon = val.second;

        cout << "Beacon " << (int) uid[10] << " : txPower = " << beacon.getTxPower()
             << ", damp = " << beacon.getDamp() << " : " <<
             (beacon.isCalibrated() ? "SUCCESS" : "FAILURE") << endl;

    }

    // We can also access individual beacons as result.at(uid) if you know uid
    // Note that result[uid] syntax does not work with a const map, at() is cleaner
    cout << "Beacons by UID : " << endl;
    for (int beacInd = 0; beacInd < 5; ++beacInd) {
        // The correct uid of the beacon
        BeaconUID uid("Chipmunk", 1, beacInd);
        const Beacon &beacon = result.at(uid);

        cout << "Beacon " << beacInd << " : txPower = " << beacon.getTxPower()
             << ", damp = " << beacon.getDamp() << " : " <<
             (beacon.isCalibrated() ? "SUCCESS" : "FAILURE") << endl;
    }

    //-------------------------------------
    // Example of accessing calibration tables
    cout << "\n CALIBRATION TABLES : \n";

    const auto &calTables = calibrator.getCalTables();

    for (const auto &ct : calTables) {
        const BeaconUID &uid = ct.first;
        const CalibrationTable  &table = ct.second;
        cout << " -------------------- \n";
        cout << " Beacon " << (int) uid[10] << "\n";

        // Loop over all rows in the table
        for (const auto & row : table)
            cout << row.first << " : " << row.second << "\n";
    }

    return 0;
}