#pragma once
// By Oleksiy Grechnyev

namespace Navigator {
namespace Beacons {

/// Config data for KalmanBeaconNavigator
struct KalmanBeaconNavigatorConfig{
    // The hard timeout (beacon is switched off, no more predictions), in seconds
    double hardTimeout = 5;

    // ======== Trilat config
    /// Do we use full 3D trilat instead of 2D ? (default = false)
    bool use3DTrilat = false;

    /// Max number of strongest (larger rssi) beacons to use on each trilateration, 0 = unlimited (so-called multilateration)
    int useStrongest = 3;

    // ======== Mesh+mask config
    /// Apply map edges
    bool useMapEdges = true;

    /// Use mesh+mask to the final position
    bool useMeshMask = true;
};

}
}
