//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

#include <mutex>
#include <memory>

#include "./TrajectoryDetection.h"
#include "./ToGlobal.h"

#include "./AbstractAccelNavigator.h"
#include "./AccelConfig.h"

namespace Navigator {
namespace Accel {

    /** @brief
     *
     */
class StandardAccelNavigator : public AbstractAccelNavigator{
public: //==== Methods
    /** @brief Constructor
     *
     * For the accelerometer navigation you need an initial position.
     * Which is supposed to be obtained by the BLE navigation.
     *
     * @param[in] rMesh   Mesh+masktable,  nullptr disables all map functions
     * @param[in] posX    Initial X position
     * @param[in] posY    Initial Y position
     * @param[in] config  Configuration, optional (default if not specified)
     */
    StandardAccelNavigator(const std::shared_ptr<Mesh::RectanMesh> &rMesh,
                           double posX,
                           double posY,
                           const AccelConfig & config = AccelConfig()):
        trajectoryDetection(rMesh, posX, posY, config),
        toGlobal(config)
    {}

    /** @brief Process an accelerometer data packet and return position
     *
     * @param[in] ard Accelerometer data packet
     * @return        Position
     */
    virtual const Math::Position3D  & process(const AccelReceivedData &ard) override;

    /// Get last position
    virtual const Math::Position3D  & getLastPosition() const override {
        return lastPosition;
    }

    /// Get delta and reset it to 0 (thread safe)
    virtual Math::Position2D getResetDelta() override;

private: //===== Data
    /// ZUPT algorithm, walls, mesh
    TrajectoryDetection trajectoryDetection;

    /// Rotation to global coordinates, filter step detection
    ToGlobal toGlobal;

    /// Last position
    Math::Position3D lastPosition;

    /// The raw shift (delta) from the last checked position, no mesh/mask here, for the particle navigator
    Math::Position2D delta{0, 0};

    /// Mutex protecting delta
    std::mutex deltaMutex;
};
}
}


