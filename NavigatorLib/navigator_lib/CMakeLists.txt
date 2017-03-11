cmake_minimum_required(VERSION 3.0)
project(navigator_lib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        INavigator.h
        OutputNavigationData.h
        InputNavigationData.h
        #
        beacon/Beacon.h
        beacon/Position3D.h
        beacon/BeaconUID.h
        beacon/BeaconReceivedData.h
        beacon/AbstractBeaconNavigator.h
        beacon/TrilatBeaconNavigator.cpp beacon/TrilatBeaconNavigator.h
        #
        filter/IFilter.h
        filter/NoFilter.h
        filter/AlphaBetaFilter.cpp filter/AlphaBetaFilter.h)

add_library(navigator_lib STATIC ${SOURCE_FILES})
