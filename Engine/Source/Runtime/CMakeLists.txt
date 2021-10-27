cmake_minimum_required(VERSION 3.20)

add_compile_definitions(WHEEL_DYNAMIC_LIBRARY)
add_compile_definitions(WHEEL_PLATFORM_MAC)

include_directories(../ThirdParty/spdlog/include)

set(SRC_CORE
        Core/Core.h
        Core/EntryPoint.h
        Core/Application.h
        Core/Application.cpp
        Core/Log.h
        Core/Log.cpp)

source_group(Wheel\\\\Core FILES ${SRC_CORE})

add_library(Engine SHARED ${SRC_CORE})