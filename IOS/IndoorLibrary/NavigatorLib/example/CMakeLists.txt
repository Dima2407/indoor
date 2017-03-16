cmake_minimum_required(VERSION 3.0)
project(example)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(
                    ../include/
                    )

set(SOURCE_FILES
        main.cpp
        )

add_executable(example ${SOURCE_FILES})
target_link_libraries(example Navigator)
