cmake_minimum_required(VERSION 3.20)

include_directories(../Engine/Source/Runtime)
include_directories(../Engine/Source/ThirdParty/spdlog/include)

set(WHEEL_LIB ${CMAKE_BINARY_DIR}/../lib/libEngine.dylib)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(Game Source/main.cpp)

target_link_libraries(Game ${WHEEL_LIB})
