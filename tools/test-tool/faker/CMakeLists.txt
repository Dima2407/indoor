cmake_minimum_required(VERSION 3.0)
project(faker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FakeEngine.cpp FakeEngine.h BeaconTime.cpp BeaconTime.h BeaconTimeList.cpp BeaconTimeList.h FakerConfig.cpp FakerConfig.h)
add_executable(faker ${SOURCE_FILES})

target_link_libraries(faker common_lib)