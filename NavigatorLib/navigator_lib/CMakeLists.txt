cmake_minimum_required(VERSION 3.0)
project(navigator_lib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        INavigator.h
        OutputNavigationData.h
        InputNavigationData.h
        #
        Beacons/Beacon.h
        Beacons/Position3D.h
        Beacons/BeaconUID.h
        Beacons/BeaconReceivedData.h
        Beacons/AbstractBeaconNavigator.h
        Beacons/TrilatBeaconNavigator.cpp Beacons/TrilatBeaconNavigator.h
        Beacons/BeaconProcessor.h
        #
        Math/Filter/IFilter.h
        Math/Filter/NoFilter.h
        Math/Filter/AlphaBetaFilter.cpp Math/Filter/AlphaBetaFilter.h
        Math/Filter/RingBuffer.h
        Math/Filter/MovingAverageFilter.cpp Math/Filter/MovingAverageFilter.h)

add_library(navigator_lib STATIC ${SOURCE_FILES})
