cmake_minimum_required(VERSION 3.0)
project(tester)

set(CMAKE_CXX_STANDARD 11)

# Include path to tracking lib
include_directories(tracking_lib)

# Build tracking lib
add_subdirectory(tracking_lib)

set(SOURCE_FILES main.cpp)
add_executable(tester ${SOURCE_FILES})

target_link_libraries(tester tracking_lib)