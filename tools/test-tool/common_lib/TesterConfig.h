//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_TESTERCONNFIG_H
#define TESTTOOL_TESTERCONNFIG_H


#include "PolyTrajectory.h"

namespace tester {
    /// The configuration of tester
    class TesterConfig {
    public:
        /** \brief Read Tester config from JSON
         *
         *  File example
 {
  "inBeaconsFile" : "in_beacons.json",
  "inEventsFile" : "out_measure.json",
  "point1": [ 0.2, 0.2, 0.0],
  "point2": [0.8, 0.3, 0.0],
  "ticks" : 1000,
  "skipEvents" : 4
}
         *
         * @param fileName   The JSON file name
         * @param verbose    true = print log to stdout
         *
         * @return           true if success
         *
         */
        bool readJSON(std::string fileName, bool verbose = true);

        /// Getters
        const std::string &getInBeaconsFile() const {
            return inBeaconsFile;
        }

        const std::string &getInEventsFile() const {
            return inEventsFile;
        }

        const std::string &getInRouteFile() const {
            return inRouteFile;
        }

        const PolyTrajectory &getTrajectory() const {
            return trajectory;
        }

        PolyTrajectory &getTrajectory() {
            return trajectory;
        }

        double getTicks() const {
            return ticks;
        }

        int getSkipEvents() const {
            return skipEvents;
        }

        bool isTxFromBeacons() const {
            return txFromBeacons;
        }

    private:
        /// Input: beacons file name
        std::string inBeaconsFile;

        /// Input: events file name
        std::string inEventsFile;

        /// Input: route file name
        std::string inRouteFile;

        /// PolyLinear trajectory
        PolyTrajectory trajectory;

        /// Number of timestamp ticks per time unit, normally 1000
        double ticks;

        /// Number of first events to skip
        int skipEvents;

        /// If true, use txPower from beacons file, not from events file
        bool txFromBeacons;

    };
}


#endif //TESTTOOL_TESTERCONNFIG_H
