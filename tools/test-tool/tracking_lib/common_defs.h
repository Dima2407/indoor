#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

/** \file common_types.h
 * \brief Contains a number of very important structures.
 *
 * Note: Some structures (Beacon, ObjectState) have namesakes in other files!
 */
 
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <limits>
#include <algorithm>

typedef long long timestamp_t;
typedef long long hash_t;

typedef std::list<double>      DistancesContainer;

namespace CommonConstants {
    constexpr double time_multiplicator = 1.0e-3;

    template<typename T>
    T big_value() {
        return std::numeric_limits<T>::max();
    }

    template<>
    double inline big_value<double>() {
        return 1.0e13;
    }

} // CommonConstants

// Global variables and constants, supposedly
// Unused and undefined, removed by Oleksiy Grechnyev
//extern const size_t __MAX_BEACON_HISTORY_LENGTH;        // maximum amount of stored beacon data (for each beacon)
//extern const size_t __MAX_BEACON_RAW_POS_HISTORY_LENGTH;// maximum amount of stored beacon distance
//extern const size_t __MAX_ACCELERATION_HISTORY_LENGTH;  // maximum amount of stored acceleration data
//extern const size_t __MAX_GYROSCOPE_HISTORY_LENGTH;     // maximum amount of stored gyroscope data
//extern const size_t __MAX_STATE_HISTORY_LENGTH;         // maximum amount of stored object states


/// \brief Sensor types
namespace SensorType {
    enum {
        Undefined,
        Beacon,
        Accelerometer,
        AccelerometerLinear,
        Magnetometer,
        Gyroscope
    };
}

/// Some esoteric container operation
template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
DataContainer<Data> last_elements(const DataContainer<Data> &input_data, size_t N) {
    N = std::min(input_data.size(), N);
    DataContainer<Data> output_data(N);
    std::copy_n(input_data.rbegin(), N, output_data.rbegin());
//    typename DataContainer<Data>::const_reverse_iterator rit = input_data.rbegin();
//    typename DataContainer<Data>::reverse_iterator       rot = output_data.rend();
//    for (int i=0; i<N; ++i) {
//        *(rot++) = *(rit++);
//    }
    return output_data;
}


#endif // COMMON_TYPES_H
