#pragma once
// By Oleksiy Grechnyev

#include <memory>
#include <unordered_map>

#include "./AbstractBeaconNavigator.h"
#include "./KalmanBeaconNavigatorConfig.h"
#include "./KalmanBeaconProcessor.h"
#include "./BeaconProcessor.h"
#include "Navigator/Math/Kalman/KalmanConfig.h"
#include "Navigator/Math/Position3D.h"
#include "Navigator/Mesh/RectanMesh.h"

namespace Navigator {
namespace Beacons {

class KalmanBeaconNavigator : public AbstractBeaconNavigator
{
public: // ====== Methods
    /// Constructor
    KalmanBeaconNavigator(const std::shared_ptr<Mesh::RectanMesh> &mesh = nullptr,
                          const KalmanBeaconNavigatorConfig & config = KalmanBeaconNavigatorConfig(),
                          const Math::Kalman::KalmanConfig & filterConfig = Math::Kalman::KalmanConfig()
            ) :
        mesh(mesh),
        config(config),
        filterConfig(filterConfig) {}

    /// Process a single input data -- not available
    virtual const Math::Position3D &process(const BeaconReceivedData & brd) {
        throw std::runtime_error("KalmanBeaconNavigator::process() with a singe packet is forbidden !");
    }

    /// Process a vector of input data, assuming identical timestamps
    virtual const Math::Position3D &process(const std::vector<BeaconReceivedData> & brds) override;

    /// Get last position
    virtual const Math::Position3D &getLastPosition() const override{
        return lastPosition;
    }

    /// Add a new beacon
    virtual void addBeacon(const Beacon &beacon){
        /// uid is the map key
        beaconProcessorList[beacon.getUid()] = std::make_shared<KalmanBeaconProcessor>(beacon, filterConfig);
    }

    /// Find a BeaconProcessor by uid, nullptr if not found
    virtual const std::shared_ptr<BeaconProcessor> findProcessorByUid(const BeaconUID & uid) const override;

    /// Delete a beacon by uid
    virtual void deleteBeacon(const BeaconUID &uid) override {
        beaconProcessorList.erase(uid);
    }

    /// Delete all beacons and reset
    virtual void clear() override{
        beaconProcessorList.clear();
        reset();
    }

    /// Reset filters etc but don't clear beacons
    virtual void reset() override;

    virtual const bool isInitFinished() const override {
        return true;
    }

    const std::vector<BeaconUID> &getLastTrilatUids() const {
        return lastTrilatUids;
    }

    const std::vector<Math::Trilat::TrilatRecord> &getTrilatRecords() const {
        return trilatRecords;
    }

private: //========= Methods

    /// Run the trilateration once based on current active beacons
    void runTrilat();

    /// Process a single input packet, no trilateration
    void processPacket(const BeaconReceivedData &brd);

    /// Check all beacons for the timeout using current timestamp
    void checkTimeout(double timeStamp);

    /// The post-processing with mesh and masktable
    Math::Position3D postProcess(Math::Position3D pos);

private: //========= Data
    /// The Mesh + MaskTable
    std::shared_ptr<Mesh::RectanMesh> mesh;

    /// Config for these navigator
    KalmanBeaconNavigatorConfig config;

    /// Config for Kalman Filters
    Math::Kalman::KalmanConfig filterConfig;

    /// List of beacon processors for all beacons currently in use
    std::unordered_map<BeaconUID, std::shared_ptr<KalmanBeaconProcessor>> beaconProcessorList;

    /// Last located position
    Math::Position3D lastPosition = Math::Position3D();

    /// Beacons that took part in the latest trilateration
    std::vector <BeaconUID> lastTrilatUids;

    // Trilateration records (position, distance) each
    std::vector<Math::Trilat::TrilatRecord> trilatRecords;
};

}
}
