//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#ifndef TESTERALL_ENGINE_H
#define TESTERALL_ENGINE_H

#include <vector>

#include "DoublePair.h"
#include "Vec3tList.h"
#include "MyBeacon.h"
#include "Event.h"
#include "MyBeaconList.h"
#include "EventList.h"
#include "TesterConfig.h"

namespace tester {
    /** \brief The main class of tester
     *
     *  Note: tester assumes that the event with lowest timestamp
     *  is identical to the first time of the route
     *  I.e. that timeStampOrigin corresponds to TimeOrigin
     */
    class Engine {
    public:

        /// Read data: config, beacons, events: true is success
        bool readData(bool verbose = true);

        /// Run tracking_lib and get the result XYZ(t)
        void runLocation();

        /// Compare the calculated XYZ to the expected one ang get the deltas
        void runDelta();

        /// Write the output data
        void writeData();

        /// Get max delta (for Unit)
        double getMaxDelta() const {
            return maxDelta;
        }

    private:
        /// Convert timestamp -> time, so that timeStampOrigin -> timeOrigin
        double stamp2Time(long long timestamp){
            return  timeOrigin + (timestamp - timeStampOrigin) / testerConfig.getTicks();
        }


        // Global data (with default constructors)

        /// Timestamp of the first event
        long long timeStampOrigin;

        /// Time of the first route point
        double timeOrigin;

        /// Configuration
        TesterConfig testerConfig;

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

        /// List of T, Delta points
        std::vector<DoublePair> tDelta;

        /// Max delta
        double maxDelta;

        /// Square averge delta
        double averageDelta;

    };
}


#endif //TESTERALL_ENGINE_H
