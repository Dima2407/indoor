//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include "INavigator.h"
#include "Position3D.h"
#include "BeaconReceivedData.h"

namespace navi_beacon {
    class AbstractBeaconNavigator : public navi::INavigator {
    public:
        virtual Position3D & process(BeaconReceivedData b) = 0;
    };
}


