cmake_minimum_required(VERSION 3.0)
project(unittest)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(
        ../include/
)

set(TEAMCITY_SRC
        teamcity/teamcity_cppunit.cpp teamcity/teamcity_cppunit.h
        teamcity/teamcity_messages.cpp teamcity/teamcity_messages.h
        )

set(SOURCE_FILES
        ${TEAMCITY_SRC}
        main.cpp
        mydoubleeq.h
        #
        DummyTest.cpp DummyTest.h
        #
        Math/Filter/RingBufferTest.cpp Math/Filter/RingBufferTest.h
        Math/Filter/MovingAverageFilterTest.cpp Math/Filter/MovingAverageFilterTest.h
        Math/Trilat/TrilatTest.cpp Math/Trilat/TrilatTest.h
        #
        Math/Beacons/BeaconUIDTest.cpp Math/Beacons/BeaconUIDTest.h)

add_executable(unittest ${SOURCE_FILES})
target_link_libraries(unittest Navigator cppunit)
