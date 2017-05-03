//
// Created by  Oleksiy Grechnyev on 5/3/2017.
//

#pragma once

#include <memory>

#include "Navigator/Beacons/AbstractBeaconNavigator.h"
#include "Navigator/Beacons/TrilatBeaconNavigator.h"
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
         * --
         * + StandardBeaconNavigator( mesh : std::shared_ptr<RectanMesh>)
         * ..
         * + process(const BeaconReceivedData &brd) : const Position3D &
         * + process(const std::vector<BeaconReceivedData> &brds) : const Position3D &
         * + findProcessorByUid(uid : BeaconUID) : const std::shared_ptr<BeaconProcessor>
         * ..
         * + addBeacon(beacon: const Beacon &) : void
         * + deleteBeacon(uid: const BeaconUID &) : void
         * + clear() : void
         * + reset() : void
         * + const getLastPosition() : const Math::Position3D &
         * ..
         * - postProcess(pos Position3D) : Position3D
         * }
         * note bottom
         * // BeaconNavigator with standard filters, mesh+masktable post-processing //
         * // //
         * // It is a wrapper to a TrilatBeaconNavigator  object //
         * // With a RectanMesh object for post-processing //
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
             * @param mesh      Mesh+masktable to use (nullptr for no mesh)
             */
            StandardBeaconNavigator(const std::shared_ptr<Mesh::RectanMesh> &mesh);

        public: //======== Methods
            /// Process a single input data
            const Math::Position3D &process(const BeaconReceivedData &brd) override;

            /// Process a vector of input data, assuming identical timestamps
            const Math::Position3D &process(const std::vector<BeaconReceivedData> &brds) override;

            /// Get last position
            const Math::Position3D &getLastPosition() const override {
                return lastPosition;
            }

            /// Add a new beacon
            void addBeacon(const Beacon &beacon) {
                triNav.addBeacon(beacon);
            }

            /// Add Beacons
            template <typename IterableT>
            void addBeacons(IterableT const& beacons){
                triNav.addBeacons(beacons);
            }

            /// Get all beacons
            int getBeacons(){
                return triNav.getBeacons();
            }

            /// Delete a beacon by uid
            void deleteBeacon(const BeaconUID &uid) {
                triNav.deleteBeacon(uid);
            }

            /// Delete all beacons and reset the position
            void clear() {
                triNav.clear();
                lastPosition = Math::Position3D();
            }

            /// Reset the Navigator (filters and last calculated position)
            void reset(){
                triNav.reset();
                lastPosition = Math::Position3D();
            }

            const std::shared_ptr<BeaconProcessor> findProcessorByUid(const BeaconUID & uid) const{
                return triNav.findProcessorByUid(uid);
            }

        private: //======== Methods
            /// The post-processing with mesh and masktable
            Math::Position3D postProcess(Math::Position3D pos);

        private: //=========== Fields ====
            /// The trilat navigator wrapped with this object
            TrilatBeaconNavigator triNav{
                    std::make_shared<Factory::MovingAverageFilterFactory>(3),
                    std::make_shared<Factory::NoFilterFactory>()
            };

            /// The Mesh + MaskTable
            std::shared_ptr<Mesh::RectanMesh> mesh;

            /// Last located position
            Math::Position3D lastPosition;

        };
    }
}

