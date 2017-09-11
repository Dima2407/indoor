cmake_minimum_required(VERSION 3.0)
project(parttest1)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(
                    ../../include/
                    )

file (COPY filesForTests DESTINATION .)

set(SOURCE_FILES
        main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Navigator)
