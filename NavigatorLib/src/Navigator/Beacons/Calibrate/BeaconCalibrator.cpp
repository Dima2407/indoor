//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#include <cmath>

#include "Navigator/Beacons/Calibrate/BeaconCalibrator.h"

#include "Navigator/Beacons/Calibrate/Algorithm/algorithm.h"

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            int
            BeaconCalibrator::calibrate(const std::vector<CalibrationPoint> &points, const CalibrationConfig &config) {
                using namespace std;

                // Create the calibration tables for each beacons from the input signal
                // Format: 2-column table
                // distance average_RSSI
                // For each beacon
                unordered_map<BeaconUID, Algorithm::CalibrationTable> calTables;

                // Outer loop: Loop over all calibration points
                for (CalibrationPoint const &point : points) {

                    // rssi for all packets of the current point only, broken by beacon, before averaging
                    unordered_map<BeaconUID, vector<double>> rssiMap;

                    // Loop over all packets of a point
                    for (BeaconReceivedData const &packet : point.packets) {
                        // Try to find a beacon with packet's uid
                        const BeaconUID &uid = packet.uid;
                        auto search = beaconMap.find(uid);

                        // Process packet if found, ignore otherwise
                        if (search != beaconMap.end()) {
                            // Add the rssi to rssiMap
                            if (rssiMap.count(uid) == 0)
                                rssiMap[uid] = vector<double>{packet.rssi};
                            else
                                rssiMap[uid].push_back(packet.rssi);
                        }
                    }

                    // Now rssiMap for the current point is complete

                    // Loop over all uid's in rssiMap
                    // Distances and averages are processed here
                    for (auto const &val: rssiMap) {
                        const BeaconUID &uid = val.first;

                        // Find beacon with this id
                        const Beacon &beacon = beaconMap[uid];

                        // Find average rssi
                        double averageRSSI = 0;
                        for (double d : val.second)
                            averageRSSI += d;

                        averageRSSI /= val.second.size();

                        // Calculate the distance from point to the beacon
                        double distance = beacon.getPos().distance(point.position);

                        // Add (distance, average rssi) pair to the calibration table
                        // This adds average RSSI for all beacons and the current point

                        // Create a uid entry if doesn't exist
                        if (calTables.count(uid) == 0)
                            calTables[uid] = vector<pair<double, double>>();

                        //calTables[uid].push_back(make_pair(distance, averageRSSI));
                    }
                }

                // Now the calibration table is formed
                int beaconCount = 0; // Number of beacons calibrated

                // Loop over all beacons in calTables;
                for (auto const &entry: calTables) {
                    const BeaconUID &uid = entry.first;
                    const Algorithm::CalibrationTable &table = entry.second;
                    Beacon &beacon = beaconMap[uid];

                    // Calibrate beacon : finally
                    double txPower = beacon.getTxPower(); // Iput/Output values
                    double damp = beacon.getDamp();

                    Algorithm::calibrate(table, config, txPower, damp);

                    // Store the calibration result if OK
                    if (!isnan(damp) && !isnan(txPower)) {
                        beacon.setTxPower(txPower);
                        beacon.setDamp(damp);
                        beaconCount++;
                    }
                }

                return beaconCount;
            }

            bool BeaconCalibrator::isLegit(double dist, double rssi, const CalibrationConfig &config) {

                // Check that dist is less than max dist (e.g. 5 meters)
                if (dist > config.maxDist)
                    return false;
                    // Now check the line-of-sight
                else
                    return rssi > config.kLos * dist + config.bLos;

            }
        }
    }
}
