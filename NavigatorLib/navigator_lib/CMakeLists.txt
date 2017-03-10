cmake_minimum_required(VERSION 3.0)
project(navigator_lib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Beacon.h
        Position3D.h
        BeaconUID.h
        BeaconReceivedData.h
        INavigator.h
        OutputNavigationData.h
        InputNavigationData.h
        AbstractBeaconNavigator.h
        TrilatBeaconNavigator.cpp TrilatBeaconNavigator.h
        IFilter.h
        NoFilter.h)

add_library(navigator_lib STATIC ${SOURCE_FILES})
