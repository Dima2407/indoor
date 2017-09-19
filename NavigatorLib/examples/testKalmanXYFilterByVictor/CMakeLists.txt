cmake_minimum_required(VERSION 3.0)
project(testKalmanXYFilterByVictor)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(
                    ../../include/
                    )

set(SOURCE_FILES
        main.cpp
        )

add_executable(testKalmanXYFilterByVictor ${SOURCE_FILES})
target_link_libraries(testKalmanXYFilterByVictor Navigator)
