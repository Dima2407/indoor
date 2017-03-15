cmake_minimum_required(VERSION 3.0)
project(NavigatorLib)

set(CMAKE_CXX_STANDARD 14)


## Build libNavigator.a
add_subdirectory(src)

# Build fun
add_subdirectory(fun)

# Build unittest
add_subdirectory(unittest)

# Пока нет нужды. Хватает хэдеров
#add_subdirectory(lib/Eigen)
