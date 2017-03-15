cmake_minimum_required(VERSION 3.0)
project(navigator-test)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(
        ../include/
        ../include/rapidjson/include/
)

set(TEAMCITY_SRC
    teamcity/teamcity_cppunit.cpp teamcity/teamcity_cppunit.h
    teamcity/teamcity_messages.cpp teamcity/teamcity_messages.h
    )

set(SOURCE_FILES
    ${TEAMCITY_SRC}
    cppunit_test-1.cpp
   )

add_executable(navigator-test ${SOURCE_FILES})
target_link_libraries(navigator-test Navigator cppunit)
