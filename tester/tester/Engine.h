//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#ifndef TESTERALL_ENGINE_H
#define TESTERALL_ENGINE_H

#include <vector>

#include "MyBeacon.h"

namespace tester {
    /** \brief The singleton main class of tester
     *
     * Do I need a singleton here? Not really, though it makes sense.
     * Goood exercise for me.
     */
    class Engine {
    public:
        /// Get singleton instance (and no pointers !)
        static Engine & getInstance(){
            static Engine instance;

            return instance;
        }

        /// Read beacon data
        void readBeacons();


    private:
        // Global data
        /// List of beacons
        std::vector<MyBeacon> beacons;

        /// Ban everything
        Engine(){}
        Engine(Engine const &);
        void operator=(Engine const &);
    };
}


#endif //TESTERALL_ENGINE_H
