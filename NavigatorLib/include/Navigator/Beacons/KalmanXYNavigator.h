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
            KalmanXYBeaconNavigator(const std::shared_ptr<AbstractBeaconNavigator> &navigator,
                                    const Math::KalmanXY::KalmanXYFilter filtr)
                : beaconNavigator(navigator),
                  filter(filtr)
            {}

        private:
            std::shared_ptr<AbstractBeaconNavigator> beaconNavigator;
            Math::KalmanXY::KalmanXYFilter filter;
            Math::Position3D lastPostion; // result
        };
    }
}
