cmake_minimum_required(VERSION 3.0)
project(common_lib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Event.h Event.cpp MyBeacon.h MyBeacon.cpp Vec3.h Vec3.cpp MyBeaconList.cpp MyBeaconList.h
        EventList.cpp EventList.h Vec3List.cpp Vec3List.h Util.cpp Util.h myjson.h myjson.cpp
        LinearTrajectory.cpp LinearTrajectory.h DoublePair.h Vec3t.cpp Vec3t.h Vec3tList.cpp Vec3tList.h PolyTrajectory.cpp PolyTrajectory.h)
add_library(common_lib STATIC ${SOURCE_FILES})