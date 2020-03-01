cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(singleton_lifetime VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(EXTERNAL_BOOST_DI_PATH ${PROJECT_SOURCE_DIR}/../3rdparty/di)
execute_process(COMMAND git submodule update --init -- ${EXTERNAL_BOOST_DI_PATH}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_BOOST_DI_PATH}/include)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wfatal-errors -Wl,--no-undefined)
