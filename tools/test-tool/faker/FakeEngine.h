//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#ifndef TESTERALL_FAKEENGINE_H
#define TESTERALL_FAKEENGINE_H

#include <vector>
#include <cstdlib>
#include <EventList.h>

#include "MyBeacon.h"
#include "Vec3.h"
#include "BeaconTime.h"
#include "Event.h"
#include "MyBeaconList.h"
#include "BeaconTimeList.h"
#include "FakerConfig.h"

namespace faker {

    /// Main class of faker
    class FakeEngine {


    public:
        /////////////////////////

        /// Read configuration, beacons and beacon times
        void readData();

        /// Do the actual calculation
        void run();

        /// Create events for a given MyBeacon and BeaconTime
        void createEvents(const tester::MyBeacon & beacon, const BeaconTime & beaconTime);

        // Write results (events)
        void writeResults();

    private:
        // Global data

        /// Configuration
        FakerConfig fakerConfig;

        /// List of beacons
        tester::MyBeaconList beaconList;

        /// List of events
        tester::EventList eventList;

        /// Lest of beacon time data
        BeaconTimeList beaconTimeList;

    };
}


#endif //TESTERALL_FAKEENGINE_H
