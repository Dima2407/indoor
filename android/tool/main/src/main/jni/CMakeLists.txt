cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++14")

file(GLOB_RECURSE LIBRARY "../../../../../../NavigatorLib/src/Navigator/*.cpp")

include_directories(../../../../../../NavigatorLib/include
                    ../../../../../../NavigatorLib/lib)

add_library( Navigator
             STATIC
             ${LIBRARY})

add_library( native-lib
             SHARED
             native-lib.cpp)

find_library( log-lib
              log)

target_link_libraries(
                       native-lib

                       Navigator
                       ${log-lib} )