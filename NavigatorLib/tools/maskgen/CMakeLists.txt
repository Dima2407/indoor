cmake_minimum_required(VERSION 3.0)
project(maskgen)

set(CMAKE_CXX_STANDARD 14)

# Does not need Navigator

set(SOURCE_FILES
        main.cpp
        MeshData.h
        MaskData.h computeMaskTbl.cpp computeMaskTbl.h)

add_executable(maskgen ${SOURCE_FILES})
