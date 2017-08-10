cmake_minimum_required(VERSION 3.0)
project(tools)

set(CMAKE_CXX_STANDARD 14)

# Build all tools
# Removed to speed up builds
# Uncomment what you need
#add_subdirectory(masklib)
#add_subdirectory(maskgen)


# Note: maskdemo culd be tricky with the CImg library
# Comment this if you run into errors you cannot fix
#add_subdirectory(maskdemo)
#add_subdirectory(maskdemo2)
#add_subdirectory(dijkdemo)

#add_subdirectory(maskgen2)

#add_subdirectory(acceltester)

add_subdirectory(partdemo)


