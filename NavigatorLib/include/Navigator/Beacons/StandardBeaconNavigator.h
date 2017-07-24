//
// Created by  Oleksiy Grechnyev on 5/3/2017.
//

#pragma once

#include <memory>

#include "Navigator/Beacons/AbstractBeaconNavigator.h"
#include "Navigator/Beacons/TrilatBeaconNavigator.h"
#include "Navigator/Beacons/StandardBeaconNavigatorConfig.h"
#include "Navigator/Beacons/Factory/NoFilterFactory.h"
#include "Navigator/Beacons/Factory/MovingAverageFilterFactory.h"

#include "Navigator/Mesh/RectanMesh.h"

namespace Navigator {
    namespace Beacons {
        /** @brief BeaconNavigator with standard filters, mesh+masktable post-processing
         *
         *
         * @startuml
         *
         * class StandardBeaconNavigator {
         * - triNav : TrilatBeaconNavigator
         * - lastPosition : Position3D
         * - mesh : std::shared_ptr<RectanMesh>
         * - initPosition : Position3D
         * - initFinished : bool
         * --
         * + StandardBeaconNavigator( mesh : std::shared_ptr<RectanMesh>)
         * ..
         * + process(const BeaconReceivedData &brd) : const Position3D &
         * + process(const std::vector<BeaconReceivedData> &brds) : const Position3D &
         * + findProcessorByUid(uid : BeaconUID) : const std::shared_ptr<BeaconProcessor>
         * + const getLastPosition() : const Math::Position3D &
         * + addBeacon(beacon: const Beacon &) : void
         * + deleteBeacon(uid: const BeaconUID &) : void
         * + clear() : void
         * + reset() : void
         * ..
         * + const isInitFinished() : bool
         * + const getInitPosition() const Math::Position3D &
         * ..
         * - postProcess(pos Position3D) : Position3D
         * - checkTimes() : void
         * }
         * note bottom
         * // BeaconNavigator with standard filters, init phase, mesh+masktable post-processing //
         * // //
         * // It is a wrapper to a TrilatBeaconNavigator  object //
         * // With a RectanMesh object for post-processing //
         * // Implements standard filters different for Android and iOS //
         * // Implements the 5 second Init Phase //
         * endnote
         *
         * @enduml
         *
         * class StandardBeaconNavigator .up.|> abstract AbstractBeaconNavigator
         * class TrilatBeaconNavigator --o StandardBeaconNavigator : triNav
         * class RectanMesh --o StandardBeaconNavigator : mesh
         *
         *
         */
        class StandardBeaconNavigator : public AbstractBeaconNavigator {
        public: //==========Constructor
            /**  Constructor
             *
             * @param mesh[in]      Mesh+masktable to use (nullptr for no mesh)
             * @param ios[in]       true for iOS, false for Android (different default filters)
             */
            StandardBeaconNavigator(const std::shared_ptr<Mesh::RectanMesh> &mesh, bool ios,
                                    const StandardBeaconNavigatorConfig & config = StandardBeaconNavigatorConfig());

        public: //======== Methods from AbstractBeaconNavigator implemented
            /// Process a single input data
            virtual const Math::Position3D &process(const BeaconReceivedData &brd) override;

            /// Process a vector of input data, assuming identical timestamps
            virtual const Math::Position3D &process(const std::vector<BeaconReceivedData> &brds) override;

            /// Get last position
            virtual const Math::Position3D &getLastPosition() const override {
                return lastPosition;
            }

            /// Add a new beacon
            virtual void addBeacon(const Beacon &beacon) {
                triNav.addBeacon(beacon);
            }

            /// Find a BeaconProcessor by uid, nullptr if not found
            virtual const std::shared_ptr<BeaconProcessor> findProcessorByUid(const BeaconUID & uid) const override {
                return triNav.findProcessorByUid(uid);
            }

            /// Delete a beacon by uid
            virtual void deleteBeacon(const BeaconUID &uid) override {
                triNav.deleteBeacon(uid);
            }

            /// Delete all beacons and reset the position
            virtual void clear() override {
                triNav.clear();
                lastPosition = Math::Position3D();
            }

            /// Reset the Navigator (filters and last calculated position)
            virtual void reset() override {
                triNav.reset();
                lastPosition = Math::Position3D();
            }

        public: ///========= Other methods
            bool isInitFinished() const {
                return initFinished;
            }

            const Math::Position3D &getInitPosition() const {
                return initPosition;
            }

        private: //======== Methods
            /// The post-processing with mesh and masktable
            Math::Position3D postProcess(Math::Position3D pos);

            /// Check timestamps and change navigator filters if needed
            void checkTimes();

            /// Set up the default post-init filters
            void setFilters();

        private: //=========== Fields ====
            /// Config
            StandardBeaconNavigatorConfig config;

            /// true for iOS, false for Android (different default filters)
            bool ios;

            /// The trilat navigator wrapped with this object
            TrilatBeaconNavigator triNav;

            /// The Mesh + MaskTable
            std::shared_ptr<Mesh::RectanMesh> mesh;

            /// Last located position
            Math::Position3D lastPosition;

            /// Is init phase finished yet?
            bool initFinished = false;

            /// Position after initialization
            Math::Position3D initPosition;

            /// Factoriy for setting up RSSI filters
            std::shared_ptr<Factory::IFilterFactory> rssiFactory;
            /// Factoriy for setting up distance filters
            std::shared_ptr<Factory::IFilterFactory> distanceFactory;

        };
    }
}

