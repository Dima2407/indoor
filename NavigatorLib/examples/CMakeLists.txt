cmake_minimum_required(VERSION 3.0)
project(examples)

set(CMAKE_CXX_STANDARD 14)


# Build all examples
# Removed to speed up builds
# Uncomment what you need
#add_subdirectory(example1)

#add_subdirectory(example2)

add_subdirectory(example3)

#add_subdirectory(exampleCalibrate)

# add_subdirectory(exampleDijkstra)

#add_subdirectory(exampleMesh)

#add_subdirectory(exampleMesh2)

#add_subdirectory(exampleZUPT)

#add_subdirectory(TempVictor)

add_subdirectory(exampleAccel)

add_subdirectory(testKalmanFilterByVictor)
