cmake_minimum_required(VERSION 3.0)
project(Navigator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
    ./Navigator/Beacons/TrilatBeaconNavigator.cpp
    ./Navigator/Math/Filter/AlphaBetaFilter.cpp
    ./Navigator/Math/Filter/MovingAverageFilter.cpp
    ./Navigator/Math/Trilat/trilat.cpp
)

include_directories(
        ../include/
        ../lib/
)

add_library(Navigator STATIC ${SOURCE_FILES})

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
#target_link_libraries(Navigator eigen)
