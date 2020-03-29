cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(proxy_communication VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(cpprestsdk QUIET)

# Note: cpprest cmake find modules are not installed in Ubuntu 16.04.
# I'm adding the target manually as a workaround
if(NOT cpprestsdk_FOUND)
    add_library(cpprestsdk::cpprest SHARED IMPORTED)
    set_target_properties(cpprestsdk::cpprest PROPERTIES
        IMPORTED_LOCATION             "/usr/lib/x86_64-linux-gnu/libcpprest.so"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/include/"
    )

    # We also have to add all cpprest's external dependencies
    find_package(Boost REQUIRED system)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(cpprestsdk::cpprest INTERFACE Boost::system
                                                        OpenSSL::SSL
                                                        OpenSSL::Crypto
    )

endif()

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wfatal-errors -Wl,--no-undefined)
