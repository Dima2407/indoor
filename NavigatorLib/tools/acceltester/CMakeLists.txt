cmake_minimum_required(VERSION 3.0)
project(acceltester)

set(CMAKE_CXX_STANDARD 14)



# Does not need Navigator

set(SOURCE_FILES
        main.cpp
        )

add_executable(acceltester ${SOURCE_FILES})


