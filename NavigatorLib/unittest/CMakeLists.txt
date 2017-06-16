cmake_minimum_required(VERSION 3.0)
project(unittest)

set(CMAKE_CXX_STANDARD 14)

# Include path to navigator_lib for *.h files
include_directories(
    ../include/
    )

set(TEAMCITY_SRC
    teamcity/teamcity_cppunit.cpp teamcity/teamcity_cppunit.h
    teamcity/teamcity_messages.cpp teamcity/teamcity_messages.h
    )

set(SOURCE_FILES
    ${TEAMCITY_SRC}
    main.cpp
    mydoubleeq.h
    #
    DummyTest.cpp DummyTest.h
    #
    Math/Filter/RingBufferTest.cpp Math/Filter/RingBufferTest.h
    Math/Filter/MovingAverageFilterTest.cpp Math/Filter/MovingAverageFilterTest.h
    Math/Filter/AlphaTrimmedFilterTest.cpp Math/Filter/AlphaTrimmedFilterTest.h
    #
    Math/Trilat/TrilatTest.cpp Math/Trilat/TrilatTest.h
    #
    Beacons/BeaconUIDTest.cpp Beacons/BeaconUIDTest.h
    Beacons/BeaconProcessorTest.cpp Beacons/BeaconProcessorTest.h
    Beacons/TrilatBeaconNavigatorTest.cpp Beacons/TrilatBeaconNavigatorTest.h
    Beacons/StandardBeaconNavigatorTest.cpp Beacons/StandardBeaconNavigatorTest.h
    Beacons/Calibrate/AlgorithmTest.cpp Beacons/Calibrate/AlgorithmTest.h
    Beacons/Calibrate/BeaconCalibratorTest.cpp Beacons/Calibrate/BeaconCalibratorTest.h
    #
    Mesh/RectanMeshTest.cpp Mesh/RectanMeshTest.h
    Mesh/MeshDataTest.cpp Mesh/MeshDataTest.h
    Dijkstra/GraphTest.cpp Dijkstra/GraphTest.h Dijkstra/PointGraphTest.cpp Dijkstra/PointGraphTest.h
    #
    Accel/AlgorithmZUPTTest.cpp Accel/AlgorithmZUPTTest.h
    Accel/TrajectoryDetectionTest.cpp Accel/TrajectoryDetectionTest.h
    #
    Accel/QuaternionTest.h
    )

add_executable(unittest ${SOURCE_FILES})
target_link_libraries(unittest Navigator cppunit)
