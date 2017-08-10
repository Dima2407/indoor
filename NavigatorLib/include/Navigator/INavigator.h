//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//
#pragma once

#include "Navigator/Math/Position3D.h"

namespace Navigator {
    /// Interface: parent to all navigators
    class INavigator {
    public:
        /// Calculate or get last position
        virtual Math::Position3D obtainLastPosition() = 0;

        /// virtual destructor
        virtual ~INavigator() = default;
    };
}



