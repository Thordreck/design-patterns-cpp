cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(bloom VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Boost REQUIRED)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(freetype2 REQUIRED IMPORTED_TARGET freetype2)

list(APPEND ${PROJECT_NAME}_SRCS
        src/Window.cpp
        src/TextBuffer.cpp
        src/TextRenderer.cpp
        src/MenuBar.cpp
        src/ShaderUtils.cpp
)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::freetype2)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wfatal-errors -Wl,--no-undefined)

add_executable(${PROJECT_NAME}_example src/Bloom.cpp)
target_link_libraries(${PROJECT_NAME}_example PRIVATE ${PROJECT_NAME})
target_compile_options(${PROJECT_NAME}_example PUBLIC -std=c++17)
target_compile_options(${PROJECT_NAME}_example PRIVATE -Wall -Wfatal-errors -Wl,--no-undefined)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/shaders/text.f.glsl" "${CMAKE_BINARY_DIR}"
    COMMENT "Copying shader files"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/shaders/text.v.glsl" "${CMAKE_BINARY_DIR}"
    COMMENT "Copying shader files"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/fonts/FreeMono.ttf" "${CMAKE_BINARY_DIR}"
    COMMENT "Copying font files"
)
