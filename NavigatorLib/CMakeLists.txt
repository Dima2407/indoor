cmake_minimum_required(VERSION 3.0)
project(NavigatorLib)

set(CMAKE_CXX_STANDARD 14)


## Build libNavigator.a
add_subdirectory(src)


enable_testing()
include_directories(lib/)
include_directories(lib/rapidjson_min/include)


## Tests
#add_subdirectory(./lib/teamcity-cpp)
#add_subdirectory(./lib/rapidjson/)
add_subdirectory(test)


# Build example
add_subdirectory(example)

# Build exampleCalibrate
add_subdirectory(exampleCalibrate)

# Build unittest
add_subdirectory(unittest)

# Build test-tool
add_subdirectory(test-tool)

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
