//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#ifndef TESTERALL_ENGINE_H
#define TESTERALL_ENGINE_H

#include <vector>
#include <Vec3List.h>

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

        /// Run and get the result
        void run();

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

        /// List of XYZ points from location
        Vec3List vec3List;
    };
}


#endif //TESTERALL_ENGINE_H
