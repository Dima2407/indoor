cmake_minimum_required(VERSION 3.0)
project(acceltester)

set(CMAKE_CXX_STANDARD 14)


file(COPY in_data.json DESTINATION .)

set(SOURCE_FILES

    main.cpp
    in_data.json
    iOS_angles.json
    iOS_accelerometer.json
    )

add_executable(acceltester ${SOURCE_FILES})
include_directories(../lib/rapidjson_min/include)
target_link_libraries(acceltester Navigator)


