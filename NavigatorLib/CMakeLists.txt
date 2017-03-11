cmake_minimum_required(VERSION 3.0)
project(NavigatorLib)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for include files
include_directories(navigator_lib)

# Build navigator_lib
add_subdirectory(navigator_lib)

# Build fun
add_subdirectory(fun)