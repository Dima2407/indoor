# This is the cmake-file for the Tracking Library tracking_lib
# Note bridge.cpp is not included as it has hanrdcoded android in it at present

cmake_minimum_required(VERSION 3.0)
project(tracking_lib)

# This is needed because the stupid code sometimes uses <Eigen/Name> and sometimes "Eigen/Name"
include_directories(.)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBRIDGE_LIBRARY")

set(SOURCE_FILES abstractsensor.cpp accelerometersensor.cpp amath.cpp beacon.cpp beaconsensor.cpp
        bmath.cpp common_types.cpp imath.cpp kalman_interface.cpp navigator.cpp objectstate.cpp
        smartptr.cpp utilities.cpp)

add_library(tracking_lib STATIC ${SOURCE_FILES})