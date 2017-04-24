cmake_minimum_required(VERSION 3.0)
project(masklib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        MeshData.h
        MaskData.h
        computeMaskTbl.cpp computeMaskTbl.h
        findNearest.cpp findNearest.h
        )

add_library(masklib ${SOURCE_FILES})