//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

#include "./TrajectoryDetection.h"
#include "./ToGlobal.h"

#include "./AbstractAccelNavigator.h"

namespace Navigator {
    namespace Accel {

        class StandardAccelNavigator : public AbstractAccelNavigator{
        public: //==== Methods
            StandardAccelNavigator(const std::shared_ptr<Mesh::RectanMesh> &rMesh,
                                   double posX,
                                   double posY,
                                   double mapOrientationAngle):
                    trajectoryDetection(rMesh, posX, posY),
                    toGlobal(mapOrientationAngle)
            {}

            virtual Math::Position3D process(const AccelReceivedData &ard) override;
        private: //===== Data
            TrajectoryDetection trajectoryDetection;
            ToGlobal toGlobal;
        };
    }
}


