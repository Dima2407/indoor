//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_FAKERCONFIG_H
#define TESTTOOL_FAKERCONFIG_H

#include "Vec3.h"

#include <string>

namespace faker {
    /// FakeEngine configuration
    class FakerConfig {
    public:
        /// Read config from a JSON file
        bool readJSON(std::string fileName);



    private:
        /// Start and finish of our route
        tester::Vec3 point1, point2;
        /// Start and finish time in arbitrary units (e.g. seconds)
        double t1, t2;
        /// Number of timestamp ticks per time unit
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
