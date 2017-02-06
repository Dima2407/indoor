cmake_minimum_required(VERSION 3.0)
project(test-tool)

# C++11, this is important
set(CMAKE_CXX_STANDARD 11)

# Include paths to tracking lib and common lib
include_directories(tracking_lib)
include_directories(common_lib)

# Build tracking lib
add_subdirectory(tracking_lib)

# Build common lib
add_subdirectory(common_lib)

# Build tester
add_subdirectory(tester)

# Build faker
add_subdirectory(faker)
