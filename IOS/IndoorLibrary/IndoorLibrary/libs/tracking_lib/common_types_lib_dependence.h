#ifndef COMMON_TYPES_LIB_DEPENDENCE_H
#define COMMON_TYPES_LIB_DEPENDENCE_H

#include <cmath>
#include <cstdio>
#include <algorithm>

// Global variables and constants
extern const size_t __MAX_BEACON_HISTORY_LENGTH;        // maximum amount of stored beacon data (for each beacon)
extern const size_t __MAX_BEACON_RAW_POS_HISTORY_LENGTH;// maximum amount of stored beacon distance
extern const size_t __MAX_ACCELERATION_HISTORY_LENGTH;  // maximum amount of stored acceleration data
extern const size_t __MAX_GYROSCOPE_HISTORY_LENGTH;     // maximum amount of stored gyroscope data
extern const size_t __MAX_STATE_HISTORY_LENGTH;         // maximum amount of stored object states

//Sensor types
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

// General methods to work with common types
std::vector<double> getRssiVectorFromMeasurements(const BeaconMeasurementsContainer &);
std::vector<double> getTxVectorFromMeasurements  (const BeaconMeasurementsContainer &);
std::vector<time_t>   getTimestampVectorFromMeasurements(const BeaconMeasurementsContainer &);

template <class Data, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
DataContainer<Data> last_elements(const DataContainer<Data> &input_data, size_t N);

// Templates realization

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

#endif // COMMON_TYPES_LIB_DEPENDENCE_H
