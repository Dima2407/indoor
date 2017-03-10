//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

namespace navi_beacon {

    /// Filter interface
    class IFilter {
    public:
        /// Run a double through the filter and get the result
        virtual double run(double in) = 0;
    };
}


