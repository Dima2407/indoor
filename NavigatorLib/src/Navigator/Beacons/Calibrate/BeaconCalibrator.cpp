//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#include <cmath>

#include "Navigator/Beacons/Calibrate/BeaconCalibrator.h"


namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            const std::unordered_map<BeaconUID, Beacon> &
            BeaconCalibrator::calibrate(const std::vector<CalibrationPoint> &points, const CalibrationConfig &config) {
                using namespace std;


                // Now we have input calibration points with packets from different beacons
                // We have to break them down by beacons, average them (for each point+beacon)
                // And then convert calibration point position into distance to beacon

                // We start with a clean calibration table. For now at least.
                calTables.clear();

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

                        // Find the average rssi
                        double averageRSSI = 0;
                        for (double d : val.second)
                            averageRSSI += d;

                        averageRSSI /= val.second.size();

                        // Calculate the distance from point to the beacon
                        double distance = beacon.getPos().distance(point.position);

                        // Check if the distance is legit
                        if (isLegit(distance, averageRSSI, config)) {
                            // Add (distance, average rssi) pair to the calibration table
                            // This adds average RSSI for all beacons and the current point

                            // Create a uid entry if doesn't exist
                            if (calTables.count(uid) == 0)
                                calTables[uid] = vector<pair<double, double>>();

                            calTables[uid].push_back(make_pair(distance, averageRSSI));
                        }

                    }
                }

                // Now the calibration table is finished, ready to calibrate

                // Loop over all beacons in calTables;
                for (auto const &entry: calTables) {
                    const BeaconUID &uid = entry.first;
                    const Algorithm::CalibrationTable &table = entry.second;
                    Beacon &beacon = beaconMap.at(uid);

                    // Calibrate beacon : finally
                    // Get previous values (not used currently)
                    double txPower = beacon.getTxPower(); // Input/Output values
                    double damp = beacon.getDamp();

                    Algorithm::calibrate(table, config, txPower, damp);

                    // Store the calibration result if OK
                    // In the present version damp<=0 is discarded
                    if (!isnan(damp) && !isnan(txPower) && damp > 0) {
                        beacon.setTxPower(txPower);
                        beacon.setDamp(damp);
                        beacon.setCalibrated(true);
                    }
                }

                return beaconMap;
            }
//================================================================================

            bool BeaconCalibrator::isLegit(double dist, double rssi, const CalibrationConfig &config) {
                using namespace std;

                // Invalid if dist is greater than max dist (e.g. 5 meters), or <=0
                if (dist > config.maxDist || dist <= 0)
                    return false;
                else {
                    // Now check the line-of-sight
                    double temp = config.kLos * 10 * log10(dist) + config.bLos;
                    return rssi > temp;
                }
            }
//================================================================================

        }
    }
}
