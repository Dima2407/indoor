cmake_minimum_required(VERSION 3.0)
project(Navigator)

set(CMAKE_CXX_STANDARD 14)
set(arch arm64)

set(SOURCE_FILES
        ../include/Navigator.h
        ../include/Navigator/INavigator.h
        #
        ../include/Navigator/Beacons/AbstractBeaconNavigator.h
        ./Navigator/Beacons/TrilatBeaconNavigator.cpp ../include/Navigator/Beacons/TrilatBeaconNavigator.h
        ../include/Navigator/Beacons/StandardBeaconNavigatorConfig.h
        ../include/Navigator/Beacons/KalmanBeaconNavigatorConfig.h
        ./Navigator/Beacons/StandardBeaconNavigator.cpp ../include/Navigator/Beacons/StandardBeaconNavigator.h
        ./Navigator/Beacons/KalmanBeaconNavigator.cpp ../include/Navigator/Beacons/KalmanBeaconNavigator.h
        ../include/Navigator/Beacons/Beacon.h
        ../include/Navigator/Beacons/BeaconUID.h
        ../include/Navigator/Beacons/BeaconReceivedData.h
        ./Navigator/Beacons/BeaconProcessor.cpp ../include/Navigator/Beacons/BeaconProcessor.h
        ./Navigator/Beacons/KalmanBeaconProcessor.cpp ../include/Navigator/Beacons/KalmanBeaconProcessor.h
        #
        ./Navigator/Math/Position3D.cpp ../include/Navigator/Math/Position3D.h
        ./Navigator/Math/Filter/AlphaBetaFilter.cpp ../include/Navigator/Math/Filter/AlphaBetaFilter.h
        ./Navigator/Math/Filter/AlphaTrimmedFilter.cpp ../include/Navigator/Math/Filter/AlphaTrimmedFilter.h
        ./Navigator/Math/Filter/MovingAverageFilter.cpp ../include/Navigator/Math/Filter/MovingAverageFilter.h
        ./Navigator/Math/Trilat/trilat.cpp ../include/Navigator/Math/Trilat/TrilatRecord.h
        ../include/Navigator/Math/Filter/IFilter.h
        ../include/Navigator/Math/Filter/NoFilter.h
        ../include/Navigator/Math/Filter/RingBuffer.h
        ./Navigator/Math/Kalman/KalmanFilter.cpp ../include/Navigator/Math/Kalman/KalmanFilter.h
        ./Navigator/Math/KalmanXY/KalmanXYFilter.cpp ../include/Navigator/Math/KalmanXY/KalmanXYFilter.h
        ../include/Navigator/Math/Kalman/KalmanConfig.h
        ../include/Navigator/Math/KalmanXY/KalmanXYConfig.h
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
        ../include/Navigator/Mesh/MeshData.h
        ./Navigator/Mesh/RectanMesh.cpp ../include/Navigator/Mesh/RectanMesh.h
        #
        ../include/Navigator/Dijkstra/Edge.h
        ./Navigator/Dijkstra/Graph.cpp ../include/Navigator/Dijkstra/Graph.h
        ./Navigator/Dijkstra/PointGraph.cpp ../include/Navigator/Dijkstra/PointGraph.h
        #
        ../include/Navigator/Accel/AccelReceivedData.h
        ../include/Navigator/Accel/AccelOutputData.h
        ../include/Navigator/Accel/AbstractAccelNavigator.h
        ../include/Navigator/Accel/AccelConfig.h
        ./Navigator/Accel/StandardAccelNavigator.cpp ../include/Navigator/Accel/StandardAccelNavigator.h

        ./Navigator/Accel/TrajectoryDetection.cpp ../include/Navigator/Accel/TrajectoryDetection.h
        ./Navigator/Accel/ToGlobal.cpp ../include/Navigator/Accel/ToGlobal.h
        ../include/Navigator/Accel/TempData.h
        ./Navigator/Accel/FilterImpl.cpp ../include/Navigator/Accel/FilterImpl.h

        #
        ./Navigator/Particles/ParticleFilter.cpp ../include/Navigator/Particles/ParticleFilter.h
        ../include/Navigator/Particles/ParticleFilterConfig.h
        ../include/Navigator/Particles/ParticleNavigatorConfig.h
        Navigator/Particles/ParticleNavigator.cpp ../include/Navigator/Particles/ParticleNavigator.h
        ../include/Navigator/Particles/ParticleNavigatorConfig.h
        )

include_directories(
        ../include/
        ../lib/
)

add_library(Navigator STATIC ${SOURCE_FILES})
