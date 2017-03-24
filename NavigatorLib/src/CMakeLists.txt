cmake_minimum_required(VERSION 3.0)
project(Navigator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        ./Navigator/Beacons/TrilatBeaconNavigator.cpp
        ../include/Navigator/Beacons/Beacon.h
        #
        ./Navigator/Math/Filter/AlphaBetaFilter.cpp
        ./Navigator/Math/Filter/MovingAverageFilter.cpp
        ./Navigator/Math/Trilat/trilat.cpp
        #
        ./Navigator/Beacons/Calibrate/BeaconCalibrator.cpp ../include/Navigator/Beacons/Calibrate/BeaconCalibrator.h
        ./Navigator/Beacons/Calibrate/Algorithm/algorithm.cpp)

include_directories(
        ../include/
        ../lib/
)

add_library(Navigator STATIC ${SOURCE_FILES})

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
#target_link_libraries(Navigator eigen)
