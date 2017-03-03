# This is the cmake-file for the Tracking Library tracking_lib
# Note bridge.cpp is not included as it has hanrdcoded android in it at present

cmake_minimum_required(VERSION 3.0)
project(tracking_lib)

# This is needed because the stupid code sometimes uses <Eigen/Name> and sometimes "Eigen/Name"
# This was before refactoring, not anymore
# include_directories(.)

set(CMAKE_CXX_STANDARD 11)

# This was needed for the old tracking_lib before refactoring, not anymore
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBRIDGE_LIBRARY")

set(SOURCE_FILES
        AbstractSensor.cpp
        AccelerometerSensor.cpp
        Beacon.cpp
        BeaconSensor.cpp
        BMath.cpp
        Navigator.cpp
        ObjectState.cpp
        Point.cpp
        )

add_library(tracking_lib STATIC ${SOURCE_FILES})