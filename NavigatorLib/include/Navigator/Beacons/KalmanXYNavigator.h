//
// Created by  Victor Draban on 9/11/2017.
//

#pragma once

#include <vector>
#include <memory>

#include "Navigator/Beacons/AbstractBeaconNavigator.h"
#include "Navigator/Math/KalmanXY/KalmanXYFilter.h"
#include "Navigator/Math/KalmanXY/KalmanXYConfig.h"
#include "Navigator/Math/Position3D.h"

namespace Navigator {
    namespace Beacons {
        class KalmanXYBeaconNavigator: public AbstractBeaconNavigator {
        public:

        private:
//            std::vector<double> vec;
            std::shared_ptr<AbstractBeaconNavigator> ptr;
            Math::KalmanXY::KalmanXYFilter filter;
            Math::Position3D lastPostion; // result
        };
    }
}
