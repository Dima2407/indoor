cmake_minimum_required(VERSION 3.0)
project(maskdemo)

set(CMAKE_CXX_STANDARD 14)

file(COPY ../maskgen2/maps DESTINATION .)

include_directories(
        ../masklib
        ../CImg
)


# Does not need Navigator

set(SOURCE_FILES
        main.cpp
        )

add_executable(maskdemo ${SOURCE_FILES})

# Requires libpng at present
# I guess for Linux you'll have to replace gdi32 with something
target_link_libraries(maskdemo masklib gdi32 png)
