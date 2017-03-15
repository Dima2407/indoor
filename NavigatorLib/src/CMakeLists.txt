cmake_minimum_required(VERSION 3.0)
project(Navigator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
    INavigator.h
    ../include/Navigator/OutputNavigationData.h
    ../include/Navigator/InputNavigationData.h
    #
    Beacons/Beacon.h
    Beacons/BeaconUID.h
    Beacons/BeaconReceivedData.h
    Beacons/AbstractBeaconNavigator.h
    Beacons/TrilatBeaconNavigator.cpp Beacons/TrilatBeaconNavigator.h
    Beacons/BeaconProcessor.h
    #
    Beacons/Factory/IFilterFactory.h
    Beacons/Factory/MovingAverageFilterFactory.h
    Beacons/Factory/AlphaBetaFilterFactory.h
    Beacons/Factory/NoFilterFactory.h
    #
    Math/Position3D.h
    #
    Math/Trilat/trilat.cpp Math/Trilat/trilat.h
    #
    Math/Filter/IFilter.h
    Math/Filter/NoFilter.h
    Math/Filter/AlphaBetaFilter.cpp Math/Filter/AlphaBetaFilter.h
    Math/Filter/RingBuffer.h
    Math/Filter/MovingAverageFilter.cpp Math/Filter/MovingAverageFilter.h
    ../include/Navigator.h
)

include_directories(
        ./lib
)

add_library(Navigator STATIC ${SOURCE_FILES})
#add_subdirectory(lib/Eigen)
#target_link_libraries(navigator_lib eigen)
