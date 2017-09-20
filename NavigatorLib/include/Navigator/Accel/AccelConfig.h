#pragma once
// By Oleksiy Grechnyev

#include <vector>

#include "Navigator/Mesh/MeshConfig.h"

namespace Navigator {
namespace Accel {
/// Configuration of the Accelerometer Navigator, with reasonable defaults
struct AccelConfig{
    /// Map orientation relative to the North in degrees (Note: must be 0 at present!)
    double mapOrientationAngle = 0;

    /// Do we use a (Butterworth) filter? Shall I make it true ? (Fix unit tests then)
    bool useFilter = false;

    // The default filter coefficients are for the order-8 Butterworth filter


    // 20 mS
    /// Filter coefficients a
    std::vector<double> a{ 1.000000000000000, -6.390364563108539, 18.000338335739894, -29.171099374882836, 29.731375438327440, -19.505631768126626, 8.040995932998929, -1.903668891132583, 0.198100011559791};

    /// Filter coefficients b
    std::vector<double> b{0.00000017625537289281, 0.00000141004298314252, 0.00000493515044099882, 0.00000987030088199763, 0.00001233787610249704, 0.00000987030088199763, 0.00000493515044099882, 0.00000141004298314252, 0.00000017625537289281};

//    // 33 mS
//    /// Filter coefficients a
//    std::vector<double> a{1, -5.6403125091553754, 14.179734483869705, -20.695873101662205,
//                                19.142583364228241, -11.472236200051777, 4.344994383668622,
//                                -0.94986943840591642, 0.0916890050488007};
//
//    /// Filter coefficients b
//    std::vector<double> b{2.7733888284864122E-6, 2.2187110627891297E-5, 7.7654887197619541E-5,
//                                0.00015530977439523908, 0.00019413721799404885, 0.00015530977439523908,
//                                7.7654887197619541E-5, 2.2187110627891297E-5, 2.7733888284864122E-6};

    /// Acceleration threshold (to detect a "positive" step)
    double accThreshold = 1.075;

    // ZUPT algorithm

    /// Step adjustment coefficient of ZUPT
    double adjCoef = 33;

    /// Max velocity in m/s
    double maxV = 3.5;

    /// Gravity (acceleration unit of the accelerometer in m/s^2)
    double globG = 9.8066;

    // Dummy algorithm

    /// The average velocity at the positive step only
    double userAverageVelocity = 3.2;

    // Different aspects of a map (mesh+mask). Note: if mesh = nullptr, it turns off all map aspects.
    Mesh::MeshConfig meshConfig;
};
}
}
