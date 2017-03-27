cmake_minimum_required(VERSION 3.7)
project(NavigatorJson)

set(CMAKE_CXX_STANDARD 14)

## Boost
## -----
set( Boost_USE_STATIC_LIBS $false )
#set( BOOST_ROOT  ../lib/boost_1_63_0 )  ## Better to set CMAKE_PREFIX_PATH

## CMake 3.6.3 will fail to find. v3.7.2 works
FIND_PACKAGE( Boost 1.63 REQUIRED COMPONENTS filesystem regex )
#ADD_DEFINITIONS(-DBOOST_SYSTEM_DYN_LINK)  ## Failed on windows

set(libNavigatorRoot  ${CMAKE_SOURCE_DIR})  ## или "../"

## Include path to libNavigator for *.h files
include_directories(
        ${libNavigatorRoot}/include/
        rapidjson/include/  ## include path was set in upper layer CMakeLists.txt
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_FILES
    ./main.cpp
    ItJim/JsonDataContract.cpp
    )
add_executable(NavigatorJson ${SOURCE_FILES})
target_link_libraries(NavigatorJson Navigator ${Boost_LIBRARIES})

if(WIN32)  #and mingw
#set_target_properties(NavigatorJson PROPERTIES LINK_FLAGS --disable-shared)
set_target_properties(NavigatorJson PROPERTIES LINK_FLAGS -static -static-libgcc -static-libstdc++)
endif(WIN32)
	
## Copy folder beacons-data-files to build path, near executable.
add_custom_command(TARGET NavigatorJson
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/input
                   $<TARGET_FILE_DIR:NavigatorJson>/input
                   )

## Copy README.md
add_custom_command(TARGET NavigatorJson
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_CURRENT_SOURCE_DIR}/README.md
                   $<TARGET_FILE_DIR:NavigatorJson>/README.md
                   )