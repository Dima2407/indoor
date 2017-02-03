cmake_minimum_required(VERSION 3.0)
project(faker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyBeacon.cpp MyBeacon.h Event.cpp Event.h FakeEngine.cpp FakeEngine.h Vec3.cpp Vec3.h BeaconTime.cpp BeaconTime.h)
add_executable(faker ${SOURCE_FILES})