//
// Created by  Victor Draban on 9/11/2017.
//

#include "Navigator/Beacons/KalmanXYNavigator.h"


namespace Navigator {
    namespace Beacons {

    const Math::Position3D &KalmanXYBeaconNavigator::process(const BeaconReceivedData &brd) {
        Math::Position3D temp3D = beaconNavigator->process(brd);
        Math::Position2D temp2D(temp3D);
        temp2D = filter.process(temp2D, beaconNavigator->getLastTrilatPosition());
        lastPostion = postProcess(temp2D);
        return lastPostion;
    }

    const Math::Position3D &KalmanXYBeaconNavigator::process(const std::vector<BeaconReceivedData> &brds) {
            Math::Position3D temp3D = beaconNavigator->process(brds);
            Math::Position2D temp2D(temp3D);
            temp2D = filter.process(temp2D, beaconNavigator->getLastTrilatPosition());
            lastPostion = postProcess(temp2D);
            return lastPostion;
        }

        Math::Position2D KalmanXYBeaconNavigator::postProcess(Math::Position2D pos) {
            if (mesh != nullptr && useMeshMask)
                return Math::Position2D(mesh->process(pos));
            else if (mesh != nullptr && useMapEdges)
                return Math::Position2D(mesh->checkEdges(pos));
            else
                return pos;
        }









    }
}
