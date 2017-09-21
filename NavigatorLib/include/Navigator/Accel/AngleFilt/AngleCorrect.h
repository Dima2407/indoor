//
// Created by  Oleksiy Grechnyev on 9/21/2017.
//

#pragma once

#include "./YawFilter.h"

namespace Navigator {
    namespace Accel {
        namespace AngleFilt {
            /// Pitch, roll, yaw angle correction (Android) using MovingAvergaeFilter
            class AngleCorrect {
            public:
                AngleCorrect(double mapAngle, unsigned winSize = 20) :
                        mapAngle(mapAngle),
                        filtP(winSize),
                        filtR(winSize),
                        filtY(winSize)
                {}


                /// Correct the 3 angles -- Android version
                void correct(double &yaw, double & pitch, double & roll);

                /// Reset filters
                void reset();

            private:
                /// Map rotation angle
                double mapAngle;

                /// Yaw (aka Azimuth) filter
                YawFilter filtY;

                /// Pitch filter
                Math::Filter::MovingAverageFilter filtP;

                /// Roll filter
                Math::Filter::MovingAverageFilter filtR;

            };
        }
    }
}
