cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(interface_segregation VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wfatal-errors -Wl,--no-undefined)
