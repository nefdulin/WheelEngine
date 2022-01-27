cmake_minimum_required(VERSION 3.20)
project(stb_image CXX C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib")

add_library(stb_image STATIC
        stb_image.h
	stb_image.cpp)