//
// Created by  Oleksiy Grechnyev on 9/21/2017.
//

#pragma once

#include "Navigator/Math/Filter/MovingAverageFilter.h"
#include "Navigator/Math/Filter/IFilter.h"

namespace Navigator {
    namespace Accel {
        namespace AngleFilt {
            /// A wrapper around MovingAverageFilter for Yaw angle processing with +-360 correction
            class YawFilter : public Math::Filter::IFilter{
            public:
                explicit YawFilter(unsigned winSize) :
                        maf(winSize)
                {}

                Value process(Value in) override;

                void reset() override;

            private:
                /// MovingAverageFilter which does the real work
                Math::Filter::MovingAverageFilter maf;

                /// The previous angle, it's OK to start with 0
                double prevYaw = 0;
            };
        }
    }
}


