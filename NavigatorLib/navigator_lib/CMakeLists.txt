cmake_minimum_required(VERSION 3.0)
project(navigator_lib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        INavigator.h
        OutputNavigationData.h
        InputNavigationData.h
        #
        Beacon/Beacon.h
        Beacon/Position3D.h
        Beacon/BeaconUID.h
        Beacon/BeaconReceivedData.h
        Beacon/AbstractBeaconNavigator.h
        Beacon/TrilatBeaconNavigator.cpp Beacon/TrilatBeaconNavigator.h
        Beacon/BeaconProcessor.h
        #
        Math/IFilter.h
        Math/NoFilter.h
        Math/AlphaBetaFilter.cpp Math/AlphaBetaFilter.h
        Math/RingBuffer.h
        )

add_library(navigator_lib STATIC ${SOURCE_FILES})
