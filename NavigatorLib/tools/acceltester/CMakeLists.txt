cmake_minimum_required(VERSION 3.0)
project(acceltester)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES

    Config.cpp Config.h
    Myjson.cpp Myjson.h
    Vec3.cpp Vec3.h
    Engine.cpp Engine.h




    main.cpp

    )

add_executable(acceltester ${SOURCE_FILES})


