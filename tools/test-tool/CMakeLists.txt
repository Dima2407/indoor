cmake_minimum_required(VERSION 3.0)
project(testtool)

# C++11, this is important
set(CMAKE_CXX_STANDARD 11)

# Include paths to tracking lib, common lib
include_directories(tracking_lib)
include_directories(common_lib)

# Include rapidjson (headers only)
include_directories(rapidjson_min/include)

# Build tracking lib
add_subdirectory(tracking_lib)

# Build common lib (common classes of faker and tester)
add_subdirectory(common_lib)

# Build tester
add_subdirectory(tester)

# Build faker
add_subdirectory(faker)

# Build unit
add_subdirectory(unit)

