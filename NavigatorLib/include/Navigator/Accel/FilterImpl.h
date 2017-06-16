//
// Created by  Victor Draban on 6/15/2017.
//

#pragma once

#include "Navigator/Math/Filter/IFilter.h"
#include "Navigator/Math/Filter/RingBuffer.h"

namespace Navigator {
    namespace Accel {
        class FilterImpl:public Math::Filter::IFilter {
        public:
            FilterImpl(int winSize) :
                  bufferIn(winSize),
                  bufferOut(winSize),
                  winSize(winSize)
            {}

            virtual Value process(Value in) override;
        private:
            Math::Filter::RingBuffer<Value> bufferIn;
            Math::Filter::RingBuffer<Value> bufferOut;
            int winSize;
        };
    }
}
