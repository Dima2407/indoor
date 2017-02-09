//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_BEACONTIMELIST_H
#define TESTTOOL_BEACONTIMELIST_H

#include "BeaconTime.h"

#include <string>
#include <vector>

namespace faker {
    /// List of BeaconTime object with stream IO
    class BeaconTimeList {
    public:
        /// Read times from a DAT file (true if successful)
        bool readDAT(std::string const & fileName);

        /// Read times from a JSON file (true if successful)
        bool readJSON(std::string const & fileName);

        /// Read times from a DAT or JSON file (true if successful)
        bool readAuto(std::string const & fileName);

        // Getter
        const std::vector<BeaconTime> &getBeaconTimes() const {
            return beaconTimes;
        }

        // Non-const Getter
        std::vector<BeaconTime> &getBeaconTimes() {
            return beaconTimes;
        }

        /// Clear the list
        void clear(){
            beaconTimes.clear();
        }

    private:
        /// The list of Beacon times
        std::vector<BeaconTime> beaconTimes;
    };
}


#endif //TESTTOOL_BEACONTIMELIST_H
