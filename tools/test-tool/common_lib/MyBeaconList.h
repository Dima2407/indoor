//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#ifndef TESTTOOL_MYBEACONLIST_H
#define TESTTOOL_MYBEACONLIST_H

#include <vector>

#include "MyBeacon.h"


namespace tester {
    /** \brief A vector of tester::MyBeacon with file IO routines (DAT, JSON)
     *
     * Also implements search by hash
     * No need for constructor, the default one is fine
     */
    class MyBeaconList {
    public:

        /// Read beacons from a DAT file (true if successful)
        bool readDAT(const char * fileName);

        /// Read beacons from a JSON file (true if successful)
        bool readJSON(const char * fileName);

        /// Check if beacon with hash exists in beacons
        bool beaconExists(long long hash);

        /// Find beacon by hash (assert error if not found)
        const MyBeacon & findBeacon(long long hash);

        /// Getter
        const std::vector<MyBeacon> &getBeacons() const {
            return beacons;
        }

    private:
        /// The list of beacons
        std::vector<MyBeacon> beacons;
    };
}


#endif //TESTTOOL_MYBEACONLIST_H
