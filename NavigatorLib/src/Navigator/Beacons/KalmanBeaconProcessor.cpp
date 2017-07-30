// By Oleksiy Grechnyev

#include "Navigator/Beacons/KalmanBeaconProcessor.h"

namespace Navigator {
namespace Beacons {

double KalmanBeaconProcessor::processOnlyPredict(double timeStamp)
{
    using Math::Kalman::KalmanFilter;

    if (active)
        throw std::runtime_error(" KalmanBeaconProcessor::processOnlyPredict on inactive processor !");

    // cast rssi filter to Kalman
    KalmanFilter & filter = * std::static_pointer_cast<KalmanFilter>(rssiFilter);

    // Filter rssi
    IFilter::Value rssiPair = filter.processOnlyPredict(timeStamp);

    // Calculate raw distance from the filtered RSSI
    return calculateDistance(rssiPair.val);
}

}
}
