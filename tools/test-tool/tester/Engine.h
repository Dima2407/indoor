//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#ifndef TESTERALL_ENGINE_H
#define TESTERALL_ENGINE_H

#include <vector>

#include "Vec3tList.h"
#include "MyBeacon.h"
#include "Event.h"
#include "MyBeaconList.h"
#include "EventList.h"
#include "TesterConnfig.h"

namespace tester {
    /** \brief The main class of tester
     *
     */
    class Engine {
    public:

        /// Read data: config, beacons, events
        void readData();

        /// Run tracking_lib and get the result XYZ(t)
        void runLocation();

        /// Compare the calculated XYZ to the expected one ang get the deltas
        void runDelta();

        /// Write the output data
        void writeData();

    private:
        // Global data (with default constructors)
        /// Configuration
        TesterConnfig testerConnfig;

        /// List of beacons
        MyBeaconList beaconList;

        /// List of events (timestamped measurements)
        EventList eventList;

        /// List of TXYZ points  (actual i.e. from location)
        Vec3tList txyzActual;

        /// List of TXYZ points  (expected i.e. from trajectory)
        Vec3tList txyzExpected;

        /// List of TXYZ points  (delta i.e. the difference)
        Vec3tList txyzDelta;

        /// Max delta


        /// Timestamp of the first event
        long long timeOrigin;
    };
}


#endif //TESTERALL_ENGINE_H
