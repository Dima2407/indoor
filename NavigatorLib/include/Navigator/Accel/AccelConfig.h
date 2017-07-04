#pragma once
// By Oleksiy Grechnyev

#include <vector>

namespace Navigator {
namespace Accel {
/// Configuration of the Accelerometer Navigator, with reasonable defaults
struct AccelConfig{
    /// Map orientation relative to the North in degrees
    double mapOrientationAngle = 0;

    /// Do we use a (Butterworth) filter? Shall I make it true ? (Fix unit tests then)
    bool useFilter = false;

    // The default filter coefficients are for the order-8 Butterworth filter
    // Optimized for 30 accel. packets per second

    /// Filter coefficients a
    std::vector<double> const a{1, -5.6403125091553754, 14.179734483869705, -20.695873101662205,
                                19.142583364228241, -11.472236200051777, 4.344994383668622,
                                -0.94986943840591642, 0.0916890050488007};

    /// Filter coefficients b
    std::vector<double> const b{2.7733888284864122E-6, 2.2187110627891297E-5, 7.7654887197619541E-5,
                                0.00015530977439523908, 0.00019413721799404885, 0.00015530977439523908,
                                7.7654887197619541E-5, 2.2187110627891297E-5, 2.7733888284864122E-6};

    /// Acceleration threshold (to detect a "positive" step)
    double accThreshold = 0.05;

    /// Step adjustment coefficient of ZUPT
    double adjCoef = 33;

    /// Max velocity in m/s
    double maxV = 3.5;

    /// Gravity (acceleration unit of the accelerometer in m/s^2)
    double globG = 9.8066;

    // Different aspects of a map (mesh+mask). Note: if mesh = nullptr, it turns off all map aspects.

    /// Apply map edges
    bool useMapEdges = true;

    /// Apply wall algorithm
    bool useWalls = true;

    /// Use mesh+mask to the final pposition
    bool useMeshMask = true;
};
}
}
