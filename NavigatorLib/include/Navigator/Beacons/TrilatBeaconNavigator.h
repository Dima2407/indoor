//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <unordered_map>
#include <memory>

#include "Navigator/Beacons/AbstractBeaconNavigator.h"
#include "Navigator/Beacons/BeaconProcessor.h"
#include "Navigator/Beacons/Factory/IFilterFactory.h"
#include "Navigator/Math/Trilat/Trilat.h"

#pragma once
namespace Navigator {
    namespace Beacons {

        /** @brief Trilateration-based beacon navigator
         *
         * @startuml
         * class TrilatBeaconNavigator {
         * - rssiFilterFactory : std::shared_ptr<IFilterFactory>
         * - distanceFilterFactory : std::shared_ptr<IFilterFactory>
         * - beaconProcessorList : std::unordered_map<BeaconUID, std::shared_ptr<BeaconProcessor>>
         * - lastPosition : Position3D
         * ..
         * - beaconTimeout : double
         * - use3DTrilat : bool
         * - useNearest : unsigned
         * --
         * + TrilatBeaconNavigator(rssiFilterFactory : const std::shared_ptr<IFilterFactory> &,
         *                        distanceFilterFactory : const std::shared_ptr<IFilterFactory> &)
         * ..
         * + process(const BeaconReceivedData &brd) : const Position3D &
         * + addBeacon(beacon: const Beacon &) : void
         * + deleteBeacon(uid: const BeaconUID &) : void
         * + clear() : void
         * + const getLastPosition() : const Math::Position3D &
         * }
         * note bottom
         * // This is the trilateration-based beacon navigator //
         * // You must add at least 3 beacons //
         * // And process events for at least 3 beacons //
         * // To get a nonzero result //
         * // Currently in 2D (z is ignored) //
         * endnote
         *
         * class TrilatBeaconNavigator .up.|> abstract AbstractBeaconNavigator
         * interface Factory::IFilterFactory --o TrilatBeaconNavigator : rssiFilterFactory
         * interface Factory::IFilterFactory --o TrilatBeaconNavigator : distanceFilterFactory
         * @enduml
         *
         */
        class TrilatBeaconNavigator : public AbstractBeaconNavigator {
        public:

            // -----  Public methods ------
            /// Constructor
            TrilatBeaconNavigator(const std::shared_ptr<Factory::IFilterFactory> &rssiFilterFactory,
                                  const std::shared_ptr<Factory::IFilterFactory> &distanceFilterFactory)
                    : rssiFilterFactory(rssiFilterFactory),
                      distanceFilterFactory(distanceFilterFactory) {}

            /// Process a single input data
            const Math::Position3D &process(const BeaconReceivedData &brd) override;

            /// Process a vector of input data, assuming identical timestamps
            const Math::Position3D &process(const std::vector<BeaconReceivedData> &brds) override;

            //------ Beacon operations -----

            /// Add a new beacon
            void addBeacon(const Beacon &beacon) {
                /// uid is the map key
                /// Factories create filter objects
                beaconProcessorList[beacon.getUid()] = std::make_shared<BeaconProcessor>(
                        beacon,
                        rssiFilterFactory->createFilter(),
                        distanceFilterFactory->createFilter()
                );
            }
    
            /// Add Beacons
            template <typename IterableT>
            void addBeacons(IterableT const& beacons) {
                for( const auto & b : beacons )
                    this->addBeacon(b);
            }

            int getBeacons(){
                return beaconProcessorList.size();
            }

            /// Delete a beacon by uid
            void deleteBeacon(const BeaconUID &uid) {
                beaconProcessorList.erase(uid);
            }

            /// Delete all beacons and reset the position
            void clear() {
                beaconProcessorList.clear();
                lastPosition = Math::Position3D();
            }

            const Math::Position3D &getLastPosition() const override {
                return lastPosition;
            }

        public: // ========= Config getters + setters =============
            double getBeaconTimeout() const {
                return beaconTimeout;
            }

            void setBeaconTimeout(double beaconTimeout) {
                TrilatBeaconNavigator::beaconTimeout = beaconTimeout;
            }

            bool isUse3DTrilat() const {
                return use3DTrilat;
            }

            void setUse3DTrilat(bool use3DTrilat) {
                TrilatBeaconNavigator::use3DTrilat = use3DTrilat;
            }

            unsigned int getUseNearest() const {
                return useNearest;
            }

            void setUseNearest(unsigned int useNearest) {
                TrilatBeaconNavigator::useNearest = useNearest;
            }

        private: // ========= Methods =============
            /// Run the trilateration once based on current active beacons
            void runTrilat();

            /// Process a single input packet, no trilateration
            void processPacket(const BeaconReceivedData &brd);

            /// Check all beacons for the timeout using currentt timestamp
            void checkTimeout(double timeStamp);

        private: // ======= Fields ===============
            /// The RSSI filter factory
            std::shared_ptr<Factory::IFilterFactory> rssiFilterFactory;

            /// The distance filter factory
            std::shared_ptr<Factory::IFilterFactory> distanceFilterFactory;

            /// List of beacon processors for all beacons currently in use
            std::unordered_map<BeaconUID, std::shared_ptr<BeaconProcessor>> beaconProcessorList;
            
            /// Last located position
            Math::Position3D lastPosition = Math::Position3D();

        private: // =========== Configuration fields ==================

            /// Time to keep beacon filter history data since the last signal (in seconds)
            double beaconTimeout = 10.0;

            /// Use 3D trilateration instead of the 2D one. This requires at least 4 beacons.
            bool use3DTrilat = false;

            /// How many nearest beacon to use at most (0 = unlimited), 3(4) are needed for trilat 2D(3D)
            unsigned useNearest = 0;
        };
    }
}