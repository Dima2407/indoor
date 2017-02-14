//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_FAKERCONFIG_H
#define TESTTOOL_FAKERCONFIG_H

#include "Vec3.h"
#include "PolyTrajectory.h"

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

        /// Getters
        const tester::PolyTrajectory &getTrajectory() const {
            return trajectory;
        }

        tester::PolyTrajectory &getTrajectory(){
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

        const std::string &getInRouteFile() const {
            return inRouteFile;
        }

    private:
        /// Polylinear trajectory data: array of (t, x, y, z)
        tester::PolyTrajectory trajectory;

        /// Number of timestamp ticks per time unit, normally 1000
        double ticks;

        // Input: beacons file name
        std::string inBeaconsFile;

        // Input: beacon times file name
        std::string inTimesFile;

        // Input: route file name
        std::string inRouteFile;

        // Output: events file name
        std::string outEventsFile;

    };
}


#endif //TESTTOOL_FAKERCONFIG_H
