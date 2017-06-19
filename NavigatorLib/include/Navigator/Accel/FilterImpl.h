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
            FilterImpl(int winSize=8, double a=0, double b=0) :
                  bufferIn(winSize),
                  bufferOut(winSize),
                  winSize(winSize),
                  a(a),
                  b(b)
            {}

            virtual Value process(Value in) override;
        private:
            Math::Filter::RingBuffer<Value> bufferIn;
            Math::Filter::RingBuffer<Value> bufferOut;
            int winSize;
            double a, b;

            void checkBuff(Math::Filter::RingBuffer<Value> & buffer);
        };
    }
}
