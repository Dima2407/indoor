//
// Created by  Victor Draban on 6/15/2017.
//

#include <cmath>
#include <stdexcept>

#include "Navigator/Accel/FilterImpl.h"

namespace Navigator {
    namespace Accel {

        Math::Filter::IFilter::Value FilterImpl::process(Math::Filter::IFilter::Value in) {

            Math::Filter::IFilter::Value result = in;

            checkBuff(bufferIn);
            bufferIn.push(in);

            checkBuff(bufferOut);
            bufferOut.push(result);

            return result;
        }

        void FilterImpl::checkBuff(Math::Filter::RingBuffer<Math::Filter::IFilter::Value> &buffer) {
            if (buffer.size() == winSize) {
                IFilter::Value temp;

                bool status = buffer.pop(temp);
                if (!status)
                    throw std::runtime_error("filterimpl:: ringbuffer error");
            }
        }

    }
}
