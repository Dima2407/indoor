cmake_minimum_required(VERSION 3.0)
project(tester)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyBridge.cpp MyBridge.h MyBeacon.cpp MyBeacon.h)
add_executable(tester ${SOURCE_FILES})

target_link_libraries(tester tracking_lib)