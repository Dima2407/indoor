//
// Created by  Victor Draban on 6/15/2017.
//

#include <cmath>
#include "Navigator/Accel/FilterImpl.h"

namespace Navigator {
    namespace Accel {

        Math::Filter::IFilter::Value FilterImpl::process(Math::Filter::IFilter::Value in) {
            return in;
        }

    }
}
