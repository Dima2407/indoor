//
// Created by  Oleksiy Grechnyev on 9/21/2017.
//

#include "Navigator/Accel/AngleFilt/YawFilter.h"

namespace Navigator {
    namespace Accel {
        namespace AngleFilt {

            Math::Filter::IFilter::Value YawFilter::process(Math::Filter::IFilter::Value in) {
                double yaw = in.val;

                // Angle correction
                if (yaw - prevYaw > 180.0)
                    yaw -= 360.0;
                else if (yaw - prevYaw < -180.0)
                    yaw += 360.0;

                in.val = yaw;
                prevYaw = yaw; // Save the previous value

                return maf.process(in);
            }

            void YawFilter::reset() {
                maf.reset();
                prevYaw = 0;
            }
        }
    }
}