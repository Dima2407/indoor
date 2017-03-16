cmake_minimum_required(VERSION 3.0)
project(testtool)

# C++14
set(CMAKE_CXX_STANDARD 14)

# Include path to common lib
include_directories(common_lib)

# Include path to Navigator lib
include_directories(../include)

# Include rapidjson (headers only)
include_directories(../lib/rapidjson_min/include)

# Build common lib (common classes of faker and tester)
add_subdirectory(common_lib)

# Build tester
add_subdirectory(tester)

# Build faker
add_subdirectory(faker)

# Build autotester
add_subdirectory(autotester)

