//
// Created by  Oleksiy Grechnyev on 9/21/2017.
//

#include "Navigator/Accel/AngleFilt/AngleCorrect.h"

namespace Navigator {
    namespace Accel {
        namespace AngleFilt {

            void AngleCorrect::correct(double &yaw, double &pitch, double &roll) {
                Math::Filter::IFilter::Value v(0.0, 0.0);

                // Yaw
                v.val = yaw;
                v = filtY.process(v);
                yaw = v.val;

                // Post-process yaw
                yaw -= mapAngle;
                if (yaw > 180.0)
                    yaw -= 360.0;
                else  if (yaw < - 180.0)
                    yaw += 360.0;

                // Pitch, roll
                v.val = pitch;
                v = filtP.process(v);
                pitch = v.val;

                v.val = roll;
                v = filtR.process(v);
                roll = v.val;
            }

            void AngleCorrect::reset() {
                filtY.reset();
                filtP.reset();
                filtR.reset();
            }
        }
    }
}