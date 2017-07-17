cmake_minimum_required(VERSION 3.0)
project(acceltester)

set(CMAKE_CXX_STANDARD 14)


file(COPY in_data.json DESTINATION .)
file(COPY accel.json DESTINATION .)
file(COPY angles.json DESTINATION .)


include_directories(
    ../../include
    )

set(SOURCE_FILES

    main.cpp
    myjson.cpp myjson.h
    )

add_executable(acceltester ${SOURCE_FILES})
include_directories(../lib/rapidjson_min/include)
target_link_libraries(acceltester Navigator)


