//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_TESTERCONNFIG_H
#define TESTTOOL_TESTERCONNFIG_H


#include "LinearTrajectory.h"

namespace tester {
    /// The configuration of tester
    class TesterConnfig {
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
         * @return           true if success
         */
        bool readJSON(std::string fileName);

        /// Getters
        const std::string &getInBeaconsFile() const {
            return inBeaconsFile;
        }

        const std::string &getInEventsFile() const {
            return inEventsFile;
        }

        const LinearTrajectory &getTrajectory() const {
            return trajectory;
        }

        LinearTrajectory &getTrajectory() {
            return trajectory;
        }

        double getTicks() const {
            return ticks;
        }

        int getSkipEvents() const {
            return skipEvents;
        }

    private:
        /// Input: beacons file name
        std::string inBeaconsFile;

        /// Input: events file name
        std::string inEventsFile;

        /// Linear trajectory, times t1, t2 should be calculated, not read
        LinearTrajectory trajectory;

        /// Number of timestamp ticks per time unit, normally 1000
        double ticks;

        /// Number of first events to skip
        int skipEvents;

    };
}


#endif //TESTTOOL_TESTERCONNFIG_H
