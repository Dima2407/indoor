//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_FAKERCONFIG_H
#define TESTTOOL_FAKERCONFIG_H

#include "Vec3.h"
#include "LinearTrajectory.h"

#include <string>

namespace faker {
    /// FakeEngine configuration
    class FakerConfig {
    public:
        /** \brief Read config from a JSON file, returns true if success
         *
         * File example
{
  "inBeaconsFile": "in_beacons.json",
  "inTimesFile": "in_times.dat",
  "outEventsFile": "out_measure.dat",
  "t1": 0.0,
  "point1": [ 0.2, 0.2, 0.0],
  "t2": 1.0,
  "point2": [0.8, 0.3, 0.0],
  "ticks" : 1000
}
         *
         * @param fileName   File name
         * @return           true is success
         */
        bool readJSON(std::string fileName);

        const tester::LinearTrajectory &getTrajectory() const {
            return trajectory;
        }

        double getTicks() const {
            return ticks;
        }

        const std::string &getInBeaconsFile() const {
            return inBeaconsFile;
        }

        const std::string &getInTimesFile() const {
            return inTimesFile;
        }

        const std::string &getOutEventsFile() const {
            return outEventsFile;
        }

    private:
        /// Linear trajectory data: t1, t2, point1, point2
        tester::LinearTrajectory trajectory;

        /// Number of timestamp ticks per time unit, normally 1000
        double ticks;

        // Input: beacons file name
        std::string inBeaconsFile;

        // Input: beacon times file name
        std::string inTimesFile;

        // Output: events file name
        std::string outEventsFile;

    };
}


#endif //TESTTOOL_FAKERCONFIG_H
