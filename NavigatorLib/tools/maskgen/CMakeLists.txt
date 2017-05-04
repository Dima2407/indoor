cmake_minimum_required(VERSION 3.0)
project(maskgen)

set(CMAKE_CXX_STANDARD 14)

include_directories(../masklib)


# Does not need Navigator

set(SOURCE_FILES
        main.cpp
        )

add_executable(maskgen ${SOURCE_FILES})
target_link_libraries(maskgen masklib)
