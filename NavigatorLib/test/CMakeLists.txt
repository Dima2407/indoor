cmake_minimum_required(VERSION 3.7)
project(NavigatorTest)

set(CMAKE_CXX_STANDARD 14)

set(libNavigatorRoot  ${CMAKE_SOURCE_DIR})  ## или "../"

## Include path to libNavigator for *.h files
include_directories(
        ${libNavigatorRoot}/include/
        rapidjson/include/  ## include path was set in upper layer CMakeLists.txt
)

set(TEAMCITY_SRC
    teamcity/teamcity_cppunit.cpp teamcity/teamcity_cppunit.h
    teamcity/teamcity_messages.cpp teamcity/teamcity_messages.h
    )

set(SOURCE_FILES
    ${TEAMCITY_SRC}
    cppunit_test-1.cpp
    ItJim/JsonDataContract.cpp
    CppUnit-main.cpp)

add_executable(NavigatorCppUnitTest ${SOURCE_FILES})
target_link_libraries(NavigatorCppUnitTest Navigator cppunit)

#MESSAGE( STATUS "asd  " ${CMAKE_SOURCE_DIR} )

## Copy folder beacons-data-files to build path, near executable.
add_custom_command(TARGET NavigatorCppUnitTest
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/input
                   $<TARGET_FILE_DIR:NavigatorCppUnitTest>/input
                   )


add_executable(test-gnuplot-iostream
               test-gnuplot-iostream
               ${TEAMCITY_SRC}
               )

## Find RapidJson's bug with writing NaN to string
add_executable(temp
               temp
               ItJim/JsonDataContract.cpp
               )
target_link_libraries(temp Navigator cppunit)

set( BOOST_ROOT  ../lib/boost_1_63_0 )
## CMake 3.6.3 will fail to find. v3.7.2 works
FIND_PACKAGE( Boost 1.63 REQUIRED COMPONENTS filesystem regex )
#FIND_PACKAGE( Boost 1.63 REQUIRED )
ADD_DEFINITIONS(-DBOOST_SYSTEM_DYN_LINK)
target_link_libraries(NavigatorCppUnitTest ${Boost_LIBRARIES})

