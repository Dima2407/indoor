//
// Created by  Oleksiy Grechnyev on 5/3/2017.
//

#include "Navigator/Beacons/StandardBeaconNavigator.h"

namespace Navigator {
    namespace Beacons {

        StandardBeaconNavigator::StandardBeaconNavigator(const std::shared_ptr<Mesh::RectanMesh> &mesh, bool ios,
                                                         const StandardBeaconNavigatorConfig &config) :
                mesh(mesh),
                ios(ios),
                config(config) {

            // Set up the filters for the init phase
            triNav.setRssiFilterFactory(std::make_shared<Factory::MovingAverageFilterFactory>(20));
            triNav.setDistanceFilterFactory(std::make_shared<Factory::NoFilterFactory>());

            // Configure the Trilat navigator

            // Do we use full 3D trilat instead of 2D ? (default = false)
            triNav.setUse3DTrilat(config.use3DTrilat);

            // Max number of nearest beacons to use on each trilateration, 0 = unlimited
            triNav.setUseNearest(config.useNearest);

            // Start recording history
            triNav.startHistory();
        }
        //====================================================================

        const Math::Position3D &StandardBeaconNavigator::process(const BeaconReceivedData &brd) {

            Math::Position3D pos = triNav.process(brd);

            lastPosition = postProcess(pos);

            checkTimes(); // End the init phase if it's time

            return lastPosition;
        }
        //====================================================================

        const Math::Position3D &StandardBeaconNavigator::process(const std::vector<BeaconReceivedData> &brds) {
            Math::Position3D pos = triNav.process(brds);

            lastPosition = postProcess(pos);

            checkTimes(); // End the init phase if it's time

            return lastPosition;
        }

        //====================================================================

        Math::Position3D StandardBeaconNavigator::postProcess(Math::Position3D pos) {
            // Postprocess using mesh+masktable
            if (mesh != nullptr && config.useMeshMask)
                return mesh->process(pos);
            else if (mesh != nullptr && config.useMapEdges)
                return mesh->checkEdges(pos);
            else
                return pos;
        }

        //====================================================================

        void StandardBeaconNavigator::checkTimes() {
            using namespace std;

            // First and last timestamps of triNav
            double t2 = triNav.getLastTimestamp();
            double t1 = triNav.getFirstTimestamp();

            if (!initFinished && !isnan(t1) && !isnan(t2) && t2 - t1 > config.initPhaseDuration) {
                // Finish the initialization

                initFinished = true;
                initPosition = lastPosition;

                // Stop recording history
                triNav.stopHistory();

                // Beacon timeout in seconds (default = 10)
                // After that time idle the beacon's filters are reset
                triNav.setBeaconTimeout(1.5);


                // Re-run the history
                triNav.rerunHistory(rssiFactory, distanceFactory);

                // Update the last position (and the one about to be returned by process() )
                lastPosition = triNav.getLastPosition();
            }
        }
        //====================================================================

        void StandardBeaconNavigator::setFilters() {
            using namespace std;

            // Set up new filters
            if (ios) {
                // No filters for iOS
                rssiFactory = make_shared<Factory::NoFilterFactory>();
                distanceFactory = make_shared<Factory::NoFilterFactory>();
            } else {
                // Moving average for Android
                rssiFactory = make_shared<Factory::MovingAverageFilterFactory>(3);
                distanceFactory = make_shared<Factory::NoFilterFactory>();
            }
        }

    }
}