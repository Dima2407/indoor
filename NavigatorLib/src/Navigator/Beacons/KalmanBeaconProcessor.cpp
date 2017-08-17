// By Oleksiy Grechnyev

#include "Navigator/Beacons/KalmanBeaconProcessor.h"

namespace Navigator {
namespace Beacons {

double KalmanBeaconProcessor::processOnlyPredict(double timeStamp)
{
    using Math::Kalman::KalmanFilter;

    if (!active)
        throw std::runtime_error(" KalmanBeaconProcessor::processOnlyPredict on inactive processor !");

    // Filter rssi
    IFilter::Value rssiPair = ((KalmanFilter &)(*rssiFilter)).processOnlyPredict(timeStamp);

    lastRssi = rssiPair.val; // Save rssi

    // Calculate raw distance from the filtered RSSI
    double distance = calculateDistance(rssiPair.val);
    lastDistance = distance; // Save distance but NOT timestamp !
    return distance;
}

}
}
