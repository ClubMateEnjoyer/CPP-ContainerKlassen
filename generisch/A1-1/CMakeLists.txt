cmake_minimum_required(VERSION 3.20)

project(CPP_A11)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp vec3f.cpp test11.cpp)

add_executable(main ${SOURCE_FILES})