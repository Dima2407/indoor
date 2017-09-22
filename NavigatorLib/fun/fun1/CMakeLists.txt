cmake_minimum_required(VERSION 3.0)
project(fun1)

set(CMAKE_CXX_STANDARD 14)

file(COPY in.txt DESTINATION .)

set(SOURCE_FILES
        main.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Navigator)
