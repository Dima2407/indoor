#pragma once
// By Oleksiy Grechnyev

namespace Navigator {
namespace Beacons {

/// Config data for KalmanBeaconNavigator
struct KalmanBeaconNavigatorConfig{
    // The hard timeout (beacon is switched off, no more predictions), in seconds
    double hardTimeout = 5;
};

}
}
