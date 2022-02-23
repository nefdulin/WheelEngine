cmake_minimum_required(VERSION 3.20)
project(WheelEngine CXX)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MACOSX 1)
    add_compile_definitions(WHEEL_PLATFORM_MAC)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
    add_compile_definitions(WHEEL_PLATFORM_LINUX)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(OS_WINDOWS 1)
    add_compile_definitions(WHEEL_PLATFORM_WINDOWS)
endif()

set(WHEEL_BINARY_DIR "${CMAKE_BINARY_DIR}")

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Game)

message("LIBRARY OUTPUT: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "GENERATOR: ${CMAKE_GENERATOR}")
message(STATUS "PLATFORM: ${CMAKE_SYSTEM_NAME}")