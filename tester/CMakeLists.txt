cmake_minimum_required(VERSION 3.0)
project(testerall)

set(CMAKE_CXX_STANDARD 11)

# Include path to tracking lib
include_directories(tracking_lib)

# Build tracking lib
add_subdirectory(tracking_lib)

# Build tester
add_subdirectory(tester)

# Build faker
add_subdirectory(faker)
