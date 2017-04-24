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

# Uncomment if you have Boost installed
#add_subdirectory(test)


# Build all examples
add_subdirectory(examples)

# Build all tools
add_subdirectory(tools)


# Build unittest
add_subdirectory(unittest)

# Build test-tool
add_subdirectory(test-tool)

# Build NavigatorJson
# Uncomment if you have Boost installed
#add_subdirectory(NavigatorJson)

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
