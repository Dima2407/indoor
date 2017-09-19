//
// Created by  Oleksiy Grechnyev on 5/3/2017.
//

#include "Navigator/Beacons/StandardBeaconNavigator.h"

namespace Navigator {
    namespace Beacons {

        StandardBeaconNavigator::StandardBeaconNavigator(const std::shared_ptr<Mesh::RectanMesh> &mesh, bool ios,
                                                         const StandardBeaconNavigatorConfig &config) :
                AbstractBeaconNavigator(config.meshConfig, mesh),
                ios(ios),
                config(config) {

            // Trilateration config
            // Do we use full 3D trilat instead of 2D ? (default = false)
            triNav.setUse3DTrilat(config.use3DTrilat);
            // Max number of nearest beacons to use on each trilateration, 0 = unlimited
            triNav.setUseStrongest(config.useStrongest);

            if (config.useInit) {
                // Set up the filters for the init phase
                rssiFactory = std::make_shared<Factory::MovingAverageFilterFactory>(20);
                distanceFactory = std::make_shared<Factory::NoFilterFactory>();

                // Start recording history
                triNav.startHistory();
            } else {
                setFilters(); // No init, set up post-init filters right now
            }

            // Set the chosen filter factories
            triNav.setRssiFilterFactory(rssiFactory);
            triNav.setDistanceFilterFactory(distanceFactory);
        }
        //====================================================================

        const Math::Position3D &StandardBeaconNavigator::process(const BeaconReceivedData &brd) {

            lastPosition = triNav.process(brd);

            if (mesh)
                lastPosition = mesh->process(lastPosition, meshConfig);

            if (config.useInit && !initFinished)
                checkTimes(); // End the init phase if it's time

            return lastPosition;
        }
        //====================================================================

        const Math::Position3D &StandardBeaconNavigator::process(const std::vector<BeaconReceivedData> &brds) {
            lastPosition = triNav.process(brds);

            if (mesh)
                lastPosition = mesh->process(lastPosition, meshConfig);

            if (config.useInit && !initFinished)
                checkTimes(); // End the init phase if it's time

            return lastPosition;
        }

        //====================================================================
        void StandardBeaconNavigator::checkTimes() {
            using namespace std;

            // First and last timestamps of triNav
            double t2 = triNav.getLastTimestamp();
            double t1 = triNav.getFirstTimestamp();

            if (!isnan(t1) && !isnan(t2) && t2 - t1 > config.initPhaseDuration) {
                // Finish the initialization

                initFinished = true;
                initPosition = lastPosition;

                // Stop recording history
                triNav.stopHistory();

                // Set the new filters
                setFilters();

                // Re-run the history
                triNav.rerunHistory(rssiFactory, distanceFactory);

                // Update the last position (and the one about to be returned by process() )
                lastPosition = triNav.getLastPosition();
            }
        }
        //====================================================================

        void StandardBeaconNavigator::setFilters() {
            using namespace std;

            // Beacon timeout in seconds (default = 10)
            // After that time idle the beacon's filters are reset
            triNav.setBeaconTimeout(1.5);

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