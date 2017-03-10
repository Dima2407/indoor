cmake_minimum_required(VERSION 3.0)
project(unit)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        TestClass.cpp TestClass.h
        UnitEngine.cpp UnitEngine.h
        global.cpp global.h
        teamcity_cppunit.cpp teamcity_cppunit.h
        teamcity_messages.cpp teamcity_messages.h)

add_executable(unit ${SOURCE_FILES})

target_link_libraries(unit common_lib cppunit)