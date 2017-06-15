//
// Created by  Victor Draban on 6/15/2017.
//

#pragma once

#include "Navigator/Math/Filter/IFilter.h"

namespace Navigator {
    namespace Accel {
        class FilterImpl:public Math::Filter::IFilter {
            virtual Value process(Value in) override;
        };
    }
}
