cmake_minimum_required(VERSION 3.0)
project(dijkdemo)

set(CMAKE_CXX_STANDARD 14)

file(COPY graph.txt DESTINATION .)

include_directories(
        ../CImg
        ../../include
)

set(SOURCE_FILES
        main.cpp
        )

add_executable(dijkdemo ${SOURCE_FILES})

# Requires libpng at present
# I guess for Linux you'll have to replace gdi32 with something
target_link_libraries(dijkdemo Navigator gdi32 png)
