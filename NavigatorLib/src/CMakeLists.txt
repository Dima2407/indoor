cmake_minimum_required(VERSION 3.0)
project(Navigator)

set(CMAKE_CXX_STANDARD 14)
set(arch arm64)

set(SOURCE_FILES
        ./Navigator/Beacons/TrilatBeaconNavigator.cpp
        ../include/Navigator/Beacons/Beacon.h
        ./Navigator/Beacons/BeaconProcessor.cpp ../include/Navigator/Beacons/BeaconProcessor.h
        #
        ./Navigator/Math/Filter/AlphaBetaFilter.cpp ../include/Navigator/Math/Filter/AlphaBetaFilter.h
        ./Navigator/Math/Filter/AlphaTrimmedFilter.cpp ../include/Navigator/Math/Filter/AlphaTrimmedFilter.h
        ./Navigator/Math/Filter/MovingAverageFilter.cpp
        ./Navigator/Math/Trilat/trilat.cpp
        ../include/Navigator/Math/Trilat/TrilatRecord.h
        #
        ../include/Navigator/Beacons/Factory/AlphaTrimmedFilterFactory.h
        #
        ./Navigator/Beacons/Calibrate/BeaconCalibrator.cpp ../include/Navigator/Beacons/Calibrate/BeaconCalibrator.h
        ../include/Navigator/Beacons/Calibrate/CalibrationPoint.h
        ../include/Navigator/Beacons/Calibrate/CalibrationConfig.h
        ./Navigator/Beacons/Calibrate/Algorithm/algorithm.cpp
        ./Navigator/Beacons/BeaconProcessor.cpp

        #
        ./Navigator/Mesh/RectanMesh.cpp ../include/Navigator/Mesh/RectanMesh.h)

include_directories(
        ../include/
        ../lib/
)

add_library(Navigator STATIC ${SOURCE_FILES})

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
#target_link_libraries(Navigator eigen)
