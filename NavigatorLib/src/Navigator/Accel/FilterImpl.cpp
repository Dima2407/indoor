//
// Created by  Victor Draban on 6/15/2017.
//

#include <cmath>
#include "Navigator/Accel/FilterImpl.h"

namespace Navigator {
    namespace Accel {

        Math::Filter::IFilter::Value FilterImpl::process(Math::Filter::IFilter::Value in) {

            Math::Filter::IFilter::Value result = in;

            if (bufferIn.size() == winSize) {
                IFilter::Value temp;

                bool status = bufferIn.pop(temp);
                if (!status)
                    throw runtime_error("filterimpl:: ringbuffer error");
            }
            bufferIn.push(in);


            if (bufferOut.size() == winSize) {
                IFilter::Value temp;

                bool status = bufferOut.pop(temp);
                if (!status)
                    throw runtime_error("filterimpl:: ringbuffer error");
            }
            bufferOut.push(result);

            return result;
        }

    }
}
