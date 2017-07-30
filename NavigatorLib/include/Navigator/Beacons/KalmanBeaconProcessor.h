#pragma once
// By Oleksiy Grechnyev

#include <memory>

#include "Navigator/Beacons/BeaconProcessor.h"
#include "Navigator/Math/Kalman/KalmanConfig.h"
#include "Navigator/Math/Kalman/KalmanFilter.h"

namespace Navigator {
namespace Beacons {
    /// The Kalman-Filter special version of BeaconProcessor
    class KalmanBeaconProcessor : public BeaconProcessor{
    public: // Methods
        /// Constructor
        KalmanBeaconProcessor(const Beacon &beacon, const Math::Kalman::KalmanConfig & config):
            BeaconProcessor(beacon,
                            std::make_shared<Math::Kalman::KalmanFilter>(config),
                            std::make_shared<Math::Filter::NoFilter>()
                            ) {}

        /// Process a dummy timestamp (when no RSSI arrived) using Kalman prediction
        double processOnlyPredict(double timeStamp);
    };
}
}
