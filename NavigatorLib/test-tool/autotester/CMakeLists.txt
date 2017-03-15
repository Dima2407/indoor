cmake_minimum_required(VERSION 3.0)
project(autotester)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        TestClass.cpp TestClass.h
        AutoTesterEngine.cpp AutoTesterEngine.h
        global.cpp global.h
        teamcity_cppunit.cpp teamcity_cppunit.h
        teamcity_messages.cpp teamcity_messages.h)

add_executable(autotester ${SOURCE_FILES})

target_link_libraries(autotester common_lib cppunit Navigator)