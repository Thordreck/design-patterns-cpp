cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(singleton_injection VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

enable_testing()

message("The required GTest version will be fetch and compiled.")
set(EXTERNAL_GTEST_PATH ${PROJECT_SOURCE_DIR}/../3rdparty/googletest)
execute_process(COMMAND git submodule update --init -- ${EXTERNAL_GTEST_PATH}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
option(INSTALL_GTEST "" OFF)
option(INSTALL_GMOCK "" OFF)
add_subdirectory(${EXTERNAL_GTEST_PATH} build)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wfatal-errors -Wl,--no-undefined)

target_include_directories(${PROJECT_NAME} PRIVATE ${gtest_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${gmock_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE gmock)

add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/
            ${CMAKE_CURRENT_BINARY_DIR}/resources/
)
