//
// Created by  Victor Draban on 9/11/2017.
//

#pragma once

#include <vector>
#include <memory>

#include "Navigator/Beacons/AbstractBeaconNavigator.h"
#include "Navigator/Math/KalmanXY/KalmanXYFilter.h"
#include "Navigator/Math/KalmanXY/KalmanXYConfig.h"
#include "Navigator/Math/Position3D.h"

namespace Navigator {
    namespace Beacons {
        class KalmanXYBeaconNavigator : public AbstractBeaconNavigator {
        public:
            KalmanXYBeaconNavigator(const std::shared_ptr<AbstractBeaconNavigator> &navigator,
                                    const Mesh::MeshConfig &meshConfig = Mesh::MeshConfig(),
                                    const std::shared_ptr<Mesh::RectanMesh> &mesh = nullptr)
                    : AbstractBeaconNavigator(meshConfig, mesh),
                      beaconNavigator(navigator) {}

        public:
            virtual const Math::Position3D &process(const BeaconReceivedData &brd) override;

            virtual const Math::Position3D &process(const std::vector<BeaconReceivedData> &brds) override;

            virtual const Math::Position3D &getLastPosition() const override {
                return lastPostion;
            }

            virtual Math::Position3D obtainLastPosition() override {
                return getLastPosition();
            }

            virtual void addBeacon(const Beacon &beacon) override {
                beaconNavigator->addBeacon(beacon);
            }

            template<typename IterableT>
            void addBeacons(IterableT const &beacons) {
                for (const auto &b : beacons)
                    this->addBeacon(b);
            }

            virtual const std::shared_ptr<BeaconProcessor> findProcessorByUid(const BeaconUID &uid) const override {
                return beaconNavigator->findProcessorByUid(uid);
            }

            virtual void deleteBeacon(const BeaconUID &uid) override {
                beaconNavigator->deleteBeacon(uid);
            }

            virtual void clear() override {
                beaconNavigator->clear();
            }

            virtual void reset() override {
                beaconNavigator->reset();
            }

            virtual const bool isInitFinished() const override {
                return true;
            }

        private:
            Math::Position2D postProcess(Math::Position2D pos);

            std::shared_ptr<AbstractBeaconNavigator> beaconNavigator;
            Math::KalmanXY::KalmanXYFilter filter;
            Math::Position3D lastPostion; // result
        };
    }
}
