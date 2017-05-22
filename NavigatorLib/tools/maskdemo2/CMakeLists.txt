cmake_minimum_required(VERSION 3.0)
project(maskdemo2)

set(CMAKE_CXX_STANDARD 14)

file(COPY ../maskgen2/results DESTINATION .)
file(COPY ../maskgen2/maps DESTINATION .)

include_directories(
        ../CImg
        ../../include
)

set(SOURCE_FILES
        main.cpp
        )

add_executable(maskdemo2 ${SOURCE_FILES})

# Requires libpng at present
# I guess for Linux you'll have to replace gdi32 with something
target_link_libraries(maskdemo2 Navigator gdi32 png)
