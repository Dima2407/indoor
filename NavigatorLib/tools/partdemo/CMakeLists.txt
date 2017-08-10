cmake_minimum_required(VERSION 3.0)
project(partdemo)

set(CMAKE_CXX_STANDARD 14)

file(COPY map1 DESTINATION .)
file(COPY map2 DESTINATION .)

include_directories(
        ../CImg
        ../../include
)

set(SOURCE_FILES
        Glob.h
        main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Requires libpng at present
# I guess for Linux you'll have to replace gdi32 with something
target_link_libraries(${PROJECT_NAME} Navigator gdi32 png)
