cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(design_patterns_cpp VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(specification)
