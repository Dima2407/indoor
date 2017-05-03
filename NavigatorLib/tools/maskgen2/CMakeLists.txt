cmake_minimum_required(VERSION 3.0)
project(maskgen2)

set(CMAKE_CXX_STANDARD 14)

file(COPY maps DESTINATION .)

include_directories(
        ../masklib
        ../CImg
)


# Does not need Navigator

set(SOURCE_FILES
        main.cpp
        )

add_executable(maskgen2 ${SOURCE_FILES})

# Requires libpng at present
target_link_libraries(maskgen2 masklib png)
