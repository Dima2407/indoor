cmake_minimum_required(VERSION 3.0)
project(navigator_lib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        INavigator.h
        OutputNavigationData.h
        InputNavigationData.h
        #
        Mira/Beacon.h
        Mira/Position3D.h
        Mira/BeaconUID.h
        Mira/BeaconReceivedData.h
        Mira/AbstractBeaconNavigator.h
        Mira/TrilatBeaconNavigator.cpp Mira/TrilatBeaconNavigator.h
        Mira/BeaconProcessor.h
        #
        Math/IFilter.h
        Math/NoFilter.h
        Math/AlphaBetaFilter.cpp Math/AlphaBetaFilter.h
        Math/RingBuffer.h
        )

add_library(navigator_lib STATIC ${SOURCE_FILES})
