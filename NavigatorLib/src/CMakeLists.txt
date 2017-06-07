cmake_minimum_required(VERSION 3.0)
project(Navigator)

set(CMAKE_CXX_STANDARD 14)
set(arch arm64)

set(SOURCE_FILES
        ./Navigator/Beacons/TrilatBeaconNavigator.cpp ../include/Navigator/Beacons/TrilatBeaconNavigator.h
        ./Navigator/Beacons/StandardBeaconNavigator.cpp ../include/Navigator/Beacons/StandardBeaconNavigator.h
        ../include/Navigator/Beacons/Beacon.h
        ../include/Navigator/Beacons/BeaconReceivedData.h
        ./Navigator/Beacons/BeaconProcessor.cpp ../include/Navigator/Beacons/BeaconProcessor.h
        #
        ./Navigator/Math/Filter/AlphaBetaFilter.cpp ../include/Navigator/Math/Filter/AlphaBetaFilter.h
        ./Navigator/Math/Filter/AlphaTrimmedFilter.cpp ../include/Navigator/Math/Filter/AlphaTrimmedFilter.h
        ./Navigator/Math/Filter/MovingAverageFilter.cpp
        ./Navigator/Math/Trilat/trilat.cpp
        ../include/Navigator/Math/Trilat/TrilatRecord.h
        #
        ../include/Navigator/Beacons/Factory/NoFilterFactory.h
        ../include/Navigator/Beacons/Factory/MovingAverageFilterFactory.h
        ../include/Navigator/Beacons/Factory/AlphaTrimmedFilterFactory.h
        ../include/Navigator/Beacons/Factory/AlphaBetaFilterFactory.h
        #
        ./Navigator/Beacons/Calibrate/BeaconCalibrator.cpp ../include/Navigator/Beacons/Calibrate/BeaconCalibrator.h
        ../include/Navigator/Beacons/Calibrate/CalibrationPoint.h
        ../include/Navigator/Beacons/Calibrate/CalibrationConfig.h
        ./Navigator/Beacons/Calibrate/Algorithm/algorithm.cpp ../include/Navigator/Beacons/Calibrate/Algorithm/algorithm.h
        ./Navigator/Beacons/BeaconProcessor.cpp

        #
        ./Navigator/Mesh/RectanMesh.cpp ../include/Navigator/Mesh/RectanMesh.h
        #
        ../include/Navigator/Dijkstra/Edge.h
        ./Navigator/Dijkstra/Graph.cpp ../include/Navigator/Dijkstra/Graph.h
        ./Navigator/Dijkstra/PointGraph.cpp ../include/Navigator/Dijkstra/PointGraph.h
        #
        ../include/Navigator/Accel/AccelReceivedData.h
        ../include/Navigator/Accel/AbstractAccelNavigator.h
        ./Navigator/Accel/StandardAccelNavigator.cpp  ../include/Navigator/Accel/StandardAccelNavigator.h
        )

include_directories(
        ../include/
        ../lib/
)

add_library(Navigator STATIC ${SOURCE_FILES})

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
#target_link_libraries(Navigator eigen)
