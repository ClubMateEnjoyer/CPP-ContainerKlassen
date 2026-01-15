cmake_minimum_required(VERSION 3.20)

project(CPP_A21)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp payload.cpp test21.cpp)

add_executable(test_it ${SOURCE_FILES})