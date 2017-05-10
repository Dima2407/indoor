//
// Created by  Oleksiy Grechnyev on 5/3/2017.
//

#include "Navigator/Beacons/StandardBeaconNavigator.h"

namespace Navigator {
    namespace Beacons {


        StandardBeaconNavigator::StandardBeaconNavigator(const std::shared_ptr<Mesh::RectanMesh> &mesh)  : mesh(mesh){
            // Configure the Trilat navigator

            // Beacon timeout in seconds (default = 10)
            // After that time idle the beacon's filters are reset
            triNav.setBeaconTimeout(1.5);

            // Do we use full 3D trilat instead of 2D ? (default = false)
            triNav.setUse3DTrilat(false);

            // Max number of nearest beacons to use on each trilateration
            // 0 = unlimited, default = 0
            triNav.setUseNearest(3);
        }
        //====================================================================

        const Math::Position3D &StandardBeaconNavigator::process(const BeaconReceivedData &brd) {
            Math::Position3D pos = triNav.process(brd);

            lastPosition = postProcess(pos);

            return lastPosition;
        }
        //====================================================================

        const Math::Position3D &StandardBeaconNavigator::process(const std::vector<BeaconReceivedData> &brds) {
            Math::Position3D pos = triNav.process(brds);

            lastPosition = postProcess(pos);

            return lastPosition;
        }

        //====================================================================

        Math::Position3D StandardBeaconNavigator::postProcess(Math::Position3D pos) {
            // Postprocess using mesh+masktable
            if (mesh == nullptr)
                return pos;
            else
                return mesh -> process(pos);
        }

    }
}