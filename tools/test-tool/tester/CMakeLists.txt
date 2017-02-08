cmake_minimum_required(VERSION 3.0)
project(tester)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyBridge.cpp MyBridge.h Engine.cpp Engine.h TesterConnfig.cpp TesterConnfig.h Vec3t.cpp Vec3t.h Vec3tList.cpp Vec3tList.h)
add_executable(tester ${SOURCE_FILES})

target_link_libraries(tester tracking_lib common_lib)