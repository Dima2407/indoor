cmake_minimum_required(VERSION 3.0)
project(fun)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(../navigator_lib)

set(SOURCE_FILES
        main.cpp
        )

add_executable(fun ${SOURCE_FILES})
target_link_libraries(fun navigator_lib)
