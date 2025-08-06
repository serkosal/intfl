cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(intfl)

add_executable(intfl src/main.cpp)
target_include_directories(
    intfl PRIVATE "include"
)