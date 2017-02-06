//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#ifndef TESTERALL_ENGINE_H
#define TESTERALL_ENGINE_H

#include <vector>

#include "MyBeacon.h"
#include "Event.h"

namespace tester {
    /** \brief The main class of tester
     *
     */
    class Engine {
    public:

        /// Read beacon data
        void readBeaconsDAT();

        /// Read measurement data
        void readMeasurementsDAT(const char *fileName);

        /// Run and get the result
        void run();

    private:
        // Global data (with default constructors)
        /// List of beacons
        std::vector<MyBeacon> beacons;

        /// List of events (timestamped measurements)
        std::vector<Event> events;
    };
}


#endif //TESTERALL_ENGINE_H
