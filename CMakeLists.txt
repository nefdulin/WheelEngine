cmake_minimum_required(VERSION 3.20)
project(WheelEngine)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Engine)
add_subdirectory(Game)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MACOSX 1)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(OS_WINDOWS 1)
endif()

set(WHEEL_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${WHEEL_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WHEEL_BINARY_DIR}/bin")

message(STATUS "GENERATOR: ${CMAKE_GENERATOR}")
message(STATUS "PLATFORM: ${CMAKE_SYSTEM_NAME}")