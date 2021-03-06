#ifndef IMATH_H
#define IMATH_H

#include "common_types.h"
#include "objectstate.h"

namespace Math {
    // classes

        template<class A, class B>
        class FirstValueLessThanPairComparator {
            public:
                FirstValueLessThanPairComparator() {}
                bool operator() (const std::pair<A,B> &first, const std::pair<A,B> &second) {
                    return (first.first < second.first);
                }
        };

        template<class A, class B>
        class SecondValueLessThanPairComparator {
            public:
                SecondValueLessThanPairComparator() {}
                bool operator() (const std::pair<A,B> &first, const std::pair<A,B> &second) {
                    return (first.second < second.second);
                }
        };

        class PowerTranstormator {
            private:
                double _pow;
            public:
                PowerTranstormator(double pow) : _pow(pow) {}
                template<class A>
                A operator() (const A &value) {
                    return (std::pow(value, _pow));
                }
        };

        class Multiplicator {
            public:
                Multiplicator() {}
                template<class A>
                A operator() (const A &value1, const A &value2) {
                    return (value1 * value2);
                }
        };

    // methods
        ObjectState kalman(const ObjectState &currState, const ObjectState &beaconState, const ObjectState &accState);
        Types::ObjectState kalman(const Types::ObjectState &currState, const Types::ObjectState &measure);


        //double  mean(const std::vector<double> &data, std::vector<double> &t_weights = std::vector<double>());


        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        Data  mean(const DataContainer<Data> &data, const Data &init_value = 0);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer,
                  class Weight,  template <typename DataType, typename Allocator = std::allocator<DataType> > class WeightContainer>
        Data  mean(const DataContainer<Data> &data, WeightContainer<Weight> &t_weights = WeightContainer<Weight>(), const Data &init_value = 0);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        DataContainer<Data>  powered_elments(const DataContainer<Data> &data, double pow);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        void  power_elments(DataContainer<Data> &data, double pow);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        Data  sum(const DataContainer<Data> &data, const Data &init_value = 0);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        DataContainer<Data>  cumsum(const DataContainer<Data> &data);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        void  cumsum_elements(DataContainer<Data> &data);

        template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
        Data  cov(const DataContainer<Data> &data1, const DataContainer<Data> &data2);

        std::vector<double>  mean_filter(int n, const std::vector<double> &data, const std::vector<double> &weights = std::vector<double>());

        // General smoothing function
        // prepearing data, weigths and calling appropriate subrouting))
        std::vector<double> smooth(const std::vector<double> &measurements, const std::vector<time_t> &times = std::vector<time_t>(), time_t max_time = 0);
}

// Реализация шаблонных функций
template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
Data  Math::mean(const DataContainer<Data> &data, const Data &init_value) {
    Data sum = init_value;
    for (typename DataContainer<Data>::const_iterator it = data.begin(); it != data.end(); ++it) {
        sum += *it;
    }
    double m = 1.0 / double(data.size());
    return (sum * m);
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer,
          class Weight,  template <typename DataType, typename Allocator = std::allocator<DataType> > class WeightContainer>
Data  Math::mean(const DataContainer<Data> &data, WeightContainer<Weight> &t_weights, const Data &init_value) {
    Data sum = init_value;
    typename WeightContainer<Weight>::const_iterator wit = t_weights.begin();
    for (typename DataContainer<Data>::const_iterator it = data.begin(); it != data.end(); ++it, ++wit) {
        sum += *it * *wit;
    }
    return (sum);
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
DataContainer<Data>  Math::powered_elments(const DataContainer<Data> &data, double pow) {
    DataContainer<Data> res = data;
    std::transform(data.begin(), data.end(), res.begin(), Math::PowerTranstormator(pow));
    return res;
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
void  Math::power_elments(DataContainer<Data> &data, double pow) {
    DataContainer<Data> res = data;
    std::transform(data.begin(), data.end(), data.begin(), Math::PowerTranstormator(pow));
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
Data  Math::sum(const DataContainer<Data> &data, const Data &init_value) {
    Data res = init_value;
    for (typename DataContainer<Data>::const_iterator it = data.begin(); it != data.end(); ++it) {
        res += *it;
    }
    return res;
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
DataContainer<Data>  Math::cumsum(const DataContainer<Data> &data) {
    DataContainer<Data> res = data;
    if (data.size() > 1) {
        typename DataContainer<Data>::const_iterator dit = data.begin();
        typename DataContainer<Data>::iterator rit = res.begin();
        *rit = *dit;
        ++rit; ++dit;
        for (; dit != data.end(); ++dit, ++rit) {
            typename DataContainer<Data>::const_iterator pit = rit;
            *rit = *(--pit) + *dit;
        }
    }
    return res;
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
void  Math::cumsum_elements(DataContainer<Data> &data) {
    if (data.size() > 1) {
        typename DataContainer<Data>::iterator dit = data.begin();
        for (++dit; dit != data.end(); ++dit) {
            typename DataContainer<Data>::iterator pit = dit;
            *dit += *(--pit);
        }
    }
}

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
Data  Math::cov(const DataContainer<Data> &x, const DataContainer<Data> &y) {
    assert(x.size() == y.size());
    DataContainer<Data> xy(x.size());
    std::transform(x.begin(), x.end(), y.begin(), xy.begin(), Math::Multiplicator());
    Data m_xy = Math::sum(xy) / xy.size();
    Data m_x  = Math::sum(x) / x.size();
    Data m_y  = Math::sum(y) / y.size();
    return (m_xy-m_x*m_y);
}

Types::ObjectState kalman(const Types::ObjectState &currentState, const Types::ObjectState &measurement);

#endif // IMATH_H
