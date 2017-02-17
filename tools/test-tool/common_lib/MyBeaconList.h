//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#ifndef TESTTOOL_MYBEACONLIST_H
#define TESTTOOL_MYBEACONLIST_H

#include <vector>
#include <string>

#include "MyBeacon.h"
#include "Util.h"


namespace tester {
    /** \brief A vector of tester::MyBeacon with file IO routines (DAT, JSON)
     *
     * Also implements search by hash
     * No need for constructor, the default one is fine
     */
    class MyBeaconList {
    public:

        /// Read beacons from a file, using JSON if proper extension, using DAT otherwise
        bool readAuto(std::string const &fileName, bool verbose = true);

        /// Read beacons from a DAT file (true if successful)
        bool readDAT(std::string const &fileName, bool verbose);

        /** \brief Read beacons from a JSON file (true if successful)
         *
         * File format (example with 4 beacons)
          [
            {"xyz": [0.0,  0.0,  0.0], "hash": 1, "TXpower": 1.5, "damp":  1.1},
            {"xyz": [1.0,  0.0,  0.0], "hash": 2, "TXpower": 2.1, "damp":  1.7},
            {"xyz": [0.0,  1.0,  0.0], "hash": 3, "TXpower": 0.5, "damp":  2.3},
            {"xyz": [1.0,  1.0,  0.0], "hash": 4, "TXpower": 0.7, "damp":  2.9}
          ]
         *
         * @param fileName    File name
         * @return            true is successful
         */
        bool readJSON(std::string const &fileName, bool verbose);

        /// Check if beacon with hash exists in beacons
        bool beaconExists(long long hash);

        /// Find beacon by hash (assert error if not found)
        const MyBeacon &findBeacon(long long hash);

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
