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

set(SRC_EVENT
        Event/Event.h)

set(WHEEL_SRC
        ${SRC_CORE}
        ${SRC_EVENT})

source_group(Wheel\\\\Core FILES ${SRC_CORE})
source_group(Wheel\\\\Event FILES ${SRC_EVENT})

add_library(Engine SHARED ${WHEEL_SRC})