#ifndef INXSTRAPOLATE_H
#define INXSTRAPOLATE_H

#include <utility>
#include <cassert>
#include <iterator>

namespace General {
namespace Math {
namespace DataFitting {

class LinearInxtrapolator {
    protected:
        LinearInxtrapolator();

    public:
        ~LinearInxtrapolator();

        template <class DataType, template<typename Data, typename Allocator=std::allocator<DataType> > class Container,
                  class xType, class yType, template<typename xT, typename yT> class ToPoint2DConverter>
                static yType inxstrapolate1 (const Container<DataType> & data, const xType& position, const ToPoint2DConverter<xType, yType> &c);
        template <class xType, class yType, template<typename DataType, typename Allocator=std::allocator<DataType> > class Container>
                static yType inxstrapolate2 (const Container<xType>& xData, const Container<yType>& yData, const xType& position);
};

} // DataFitting
} // Math
} // General

/** Realization **/
namespace General {
namespace Math {
namespace DataFitting {

template <class xType, class yType, template<typename DataType, typename Allocator=std::allocator<DataType> > class Container>
    yType LinearInxtrapolator::inxstrapolate2 (const Container<xType>& xData, const Container<yType>& yData, const xType& position) {
        assert(xData.size() > 0 && yData.size() == xData.size());
        // xData must be sorted in increasing order by x-value
        typename Container<xType>::const_iterator leftIt = xData.begin();
        typename Container<xType>::const_iterator rightIt = xData.begin();
        for (typename Container<xType>::const_iterator it = xData.begin(); it != xData.end(); ++it) {
            if (*it <= position) {
                leftIt = it;
            }
            if (*it >= position) {
                rightIt = it;
            }
            if (rightIt != xData.begin()) {
                break;
            }
        }
        xType right_pos;
        yType right_val;
        xType left_pos;
        yType left_val;
        if (position > *rightIt) { // extrapolate right
            typename Container<xType>::const_reverse_iterator xit = xData.rbegin();
            typename Container<yType>::const_reverse_iterator yit = yData.rbegin();
            right_pos = *xit++;
            right_val = *yit++;
            if (xit != xData.rend()) {
                left_pos  = *xit++;
                left_val  = *yit++;
            } else {
                left_pos = right_pos;
                left_val = right_val;
            }
        } else if (position < *leftIt) { // extrapolate left
            typename Container<xType>::const_iterator xit = xData.begin();
            typename Container<yType>::const_iterator yit = yData.begin();
            left_pos = *xit++;
            left_val = *yit++;
            if (xit != xData.end()) {
                right_pos  = *xit++;
                right_val  = *yit++;
            } else {
                right_pos = left_pos;
                right_val = left_val;
            }
        } else { // interpolate
            typename Container<yType>::const_iterator yit = yData.begin();
            std::advance(yit, std::distance(xData.begin(), leftIt));
            left_pos = *leftIt;
            left_val = *yit;
            yit = yData.begin();
            std::advance(yit, std::distance(xData.begin(), rightIt));
            right_pos = *rightIt;
            right_val = *yit;
        }
        xType dx = right_pos - left_pos;
        yType dy = right_val - left_val;
        yType res;
        if (dx == 0) {
            res = (right_val + left_val) / 2.0;
        } else {
            double k = dy / dx;
            res = k*(position - left_pos) + left_val;
        }
        return res;
    }

template <class DataType, template<typename Data, typename Allocator=std::allocator<DataType> > class Container,
          class xType, class yType, template<typename xT, typename yT> class ToPoint2DConverter>
    yType LinearInxtrapolator::inxstrapolate1 (const Container<DataType> & data, const xType& position, const ToPoint2DConverter<xType, yType> &converter) {
        assert(data.size() > 0);
        // data must be sorted in increasing order by x-value
        typename Container<DataType>::const_iterator leftIt = data.begin();
        typename Container<DataType>::const_iterator rightIt = data.begin();
        for (typename Container<DataType>::const_iterator it = data.begin(); it != data.end(); ++it) {
            if (converter(*it).xr() <= position) {
                leftIt = it;
            }
            if (converter(*it).xr() >= position) {
                rightIt = it;
            }
            if (rightIt != data.begin()) {
                break;
            }
        }
        xType right_pos;
        yType right_val;
        xType left_pos;
        yType left_val;
        if (position > converter(*rightIt).xr()) { // extrapolate right
            typename Container<DataType>::const_reverse_iterator it = data.rbegin();
            right_pos = converter(*it).xr();
            right_val = converter(*it++).yr();
            if (it != data.rend()) {
                left_pos = converter(*it).xr();
                left_val = converter(*it++).yr();
            } else {
                left_pos = right_pos;
                left_val = right_val;
            }
        } else if (position < converter(*leftIt).xr()) { // extrapolate left
            typename Container<DataType>::const_iterator it = data.begin();
            left_pos = converter(*it).xr();
            left_val = converter(*it++).yr();
            if (it != data.end()) {
                right_pos = converter(*it).xr();
                right_val = converter(*it++).yr();
            } else {
                right_pos = left_pos;
                right_val = left_val;
            }
        } else { // interpolate
            left_pos = converter(*leftIt).xr();
            left_val = converter(*leftIt).yr();
            right_pos = converter(*rightIt).xr();
            right_val = converter(*rightIt).yr();
        }
        xType dx = right_pos - left_pos;
        yType dy = right_val - left_val;
        yType res;
        if (dx == 0) {
            res = (right_val + left_val) / 2.0;
        } else {
            double k = dy / dx;
            res = k*(position - left_pos) + left_val;
        }
        return res;
    }

    template <class X, class Y>
    struct SimplePointType {
        SimplePointType(X x_value, Y y_value) : x(x_value), y(y_value) {}
        X x;
        Y y;

        X& xr() {return x;}
        Y& yr() {return y;}
    };

    template<class X, class Y>
    struct SimpleToPointConverter {
        SimplePointType<X,Y> operator()(X x, Y y) {
            return SimplePointType<X, Y>(x, y);
        }
    };

    template <class X, class Y>
    struct PairToPointType {
        SimplePointType<X,Y> operator() (const std::pair<X,Y> &p) {
            return SimplePointType<X,Y>(p.first, p.second);
        }
    };

} // DataFitting
} // Math
} // General

#endif // INXSTRAPOLATE_H
