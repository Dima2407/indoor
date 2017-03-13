//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//


#pragma once

#include <cstdint>
#include <vector>

namespace Navi {
    namespace beacon {
/** @brief Beacon UID. Can be compared.
 *
 *
 */
        class BeaconUID : public std::vector<std::uint8_t> {

        };
    }
}



