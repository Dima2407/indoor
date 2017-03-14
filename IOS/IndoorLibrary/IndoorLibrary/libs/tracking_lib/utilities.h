//
// Created by grey_wolf on 27.07.16.
//

#ifndef INDORNAVIIGATION_UTILITIES_H
#define INDORNAVIIGATION_UTILITIES_H

#include <algorithm>

namespace Utilities {

class TypeTransformator {
    public:
        TypeTransformator();
        template <class To, class From>
        To operator() (const From &from) {
            return static_cast<To>(from);
        }
};


// definition
template <class ToData,
          class FromData, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
DataContainer<ToData>  convert_data_to(const DataContainer<FromData> data);

template <class Data,
          template <typename DataType,    typename Allocator = std::allocator<DataType> > class ToDataContainer,
          template <typename DataType,    typename Allocator = std::allocator<DataType> > class FromDataContainer>
ToDataContainer<Data>  convert_container_to(const FromDataContainer<Data> data);

template <class ToData,   template <typename DataType,    typename Allocator = std::allocator<DataType> > class ToDataContainer,
          class FromData, template <typename DataType,    typename Allocator = std::allocator<DataType> > class FromDataContainer>
ToDataContainer<ToData>  convert_to(const FromDataContainer<FromData> data);

} // namespace Utilities



// realization

template <class ToData,
          class FromData, template <typename DataType,    typename Allocator = std::allocator<DataType> > class DataContainer>
DataContainer<ToData>  Utilities::convert_data_to(const DataContainer<FromData> data) {
    DataContainer<ToData> res(data.size());
    std::transform(data.begin(), data.end(), res.begin(), Utilities::TypeTransformator());
    return res;
}

template <class Data,
          template <typename DataType,    typename Allocator = std::allocator<DataType> > class ToDataContainer,
          template <typename DataType,    typename Allocator = std::allocator<DataType> > class FromDataContainer>
ToDataContainer<Data>  Utilities::convert_container_to(const FromDataContainer<Data> data) {
    ToDataContainer<Data> res(data.size());
    std::copy(data.begin(), data.end(), res.begin());
    return res;
}

template <class ToData,   template <typename DataType,    typename Allocator = std::allocator<DataType> > class ToDataContainer,
          class FromData, template <typename DataType,    typename Allocator = std::allocator<DataType> > class FromDataContainer>
ToDataContainer<ToData>  Utilities::convert_to(const FromDataContainer<FromData> data) {
    ToDataContainer<ToData> res(data.size());
    std::transform(data.begin(), data.end(), res.begin(), Utilities::TypeTransformator());
}

#endif //INDORNAVIIGATION_UTILITIES_H
