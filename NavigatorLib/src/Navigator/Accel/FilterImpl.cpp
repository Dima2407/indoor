//
// Created by  Victor Draban on 6/15/2017.
//

#include <cmath>
#include <stdexcept>

#include "Navigator/Accel/FilterImpl.h"

namespace Navigator {
    namespace Accel {

        Math::Filter::IFilter::Value FilterImpl::process(Math::Filter::IFilter::Value in) {
            double temp = b[0]*in.val;

            for (int i = 1; i < b.size(); ++i) {
                Math::Filter::IFilter::Value tValue;
                if (bufferIn.peekLatest(i-1, tValue))
                    temp += b[i] * tValue.val;
                else
                    break;
            }
            for (int i = 1; i < a.size(); ++i) {
                Math::Filter::IFilter::Value tValue;
                if (bufferOut.peekLatest(i-1, tValue))
                    temp -= a[i] * tValue.val;
                else
                    break;
            }
            temp /= a[0];

            Math::Filter::IFilter::Value result(temp, in.timeStamp);

            checkBuff(bufferIn);
            checkBuff(bufferOut);
            bufferIn.push(in);
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
