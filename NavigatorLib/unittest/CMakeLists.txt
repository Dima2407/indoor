cmake_minimum_required(VERSION 3.0)
project(unittest)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(../navigator_lib)

set(SOURCE_FILES
        main.cpp
        mydoubleeq.h
        teamcity_cppunit.cpp teamcity_cppunit.h
        teamcity_messages.cpp teamcity_messages.h
        #
        DummyTest.cpp DummyTest.h
        #
        Math/Filter/RingBufferTest.cpp Math/Filter/RingBufferTest.h
        Math/Filter/MovingAverageFilterTest.cpp Math/Filter/MovingAverageFilterTest.h
        )

add_executable(unittest ${SOURCE_FILES})
target_link_libraries(unittest navigator_lib cppunit)
