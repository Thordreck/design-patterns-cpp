cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(responsibility_chain_broker VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wfatal-errors -Wl,--no-undefined)
