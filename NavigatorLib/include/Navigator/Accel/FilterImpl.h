//
// Created by  Victor Draban on 6/15/2017.
//

#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Navigator/Math/Filter/IFilter.h"
#include "Navigator/Math/Filter/RingBuffer.h"

namespace Navigator {
    namespace Accel {
        class FilterImpl:public Math::Filter::IFilter {
        public:
            FilterImpl(int winSize, std::vector<double> a, std::vector<double> b) :
                  bufferIn(winSize),
                  bufferOut(winSize),
                  winSize(winSize),
                  a(a),
                  b(b)
            {
                if (winSize < std::max(a.size(), b.size())-1) {
                    throw std::runtime_error("winSize less than vector a or vector b");
                }

                if (a.size() == 0 || a[0] == 0 || b.size() == 0) {
                    throw std::runtime_error("empty vector!!");
                }
            }

            virtual Value process(Value in) override;
        private:
            Math::Filter::RingBuffer<Value> bufferIn;
            Math::Filter::RingBuffer<Value> bufferOut;
            int winSize;
            std::vector<double> a;
            std::vector<double> b;

            void checkBuff(Math::Filter::RingBuffer<Value> & buffer);
        };
    }
}
