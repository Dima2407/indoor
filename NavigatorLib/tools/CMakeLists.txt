cmake_minimum_required(VERSION 3.0)
project(tools)

set(CMAKE_CXX_STANDARD 14)

# Build all tools
add_subdirectory(masklib)
add_subdirectory(maskgen)


# Note: maskdemo culd be tricky with the CImg library
# Comment this if you run into errors you cannot fix
add_subdirectory(maskdemo)

add_subdirectory(maskgen2)
