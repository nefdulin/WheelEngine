cmake_minimum_required(VERSION 3.20)

add_compile_definitions(WHEEL_DYNAMIC_LIBRARY)
add_compile_definitions(WHEEL_PLATFORM_MAC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../ThirdParty/spdlog/include)
include_directories(../ThirdParty/glfw/include)
include_directories(../ThirdParty/glad/include)
include_directories(../ThirdParty/ImGui)
include_directories(../ThirdParty/glm)

set(SRC_CORE
        Core/Core.h
        Core/EntryPoint.h
        Core/Application.h
        Core/Application.cpp
        Core/Input.h
        Core/Log.h
        Core/Log.cpp
        Core/KeyCodes.h
        Core/MouseCodes.h
        Core/Window.h
        Core/Layer.h
        Core/Layer.cpp
        Core/LayerStack.h
        Core/LayerStack.cpp)

set(SRC_EVENT
        Events/Event.h
        Events/ApplicationEvent.h
        Events/KeyEvent.h
        Events/MouseEvent.h)

set(SRC_RENDERER
        Renderer/GraphicsContext.h
        Renderer/Renderer.h
        Renderer/Renderer.cpp
        Renderer/Buffer.h
        Renderer/Buffer.cpp)

set(SRC_PLATFORM
        Platform/OpenGL/OpenGLContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLBuffer.h
        Platform/OpenGL/OpenGLBuffer.cpp
        Platform/Mac/MacWindow.h
        Platform/Mac/MacWindow.cpp
        Platform/Mac/MacInput.cpp)

set(SRC_IMGUI
        ImGui/ImGuiBuild.cpp
        ImGui/ImGuiLayer.h
        ImGui/ImGuiLayer.cpp)

set(WHEEL_SRC
        ${SRC_CORE}
        ${SRC_EVENT}
        ${SRC_RENDERER}
        ${SRC_PLATFORM}
        ${SRC_IMGUI})

source_group(Wheel\\\\Core FILES ${SRC_CORE})
source_group(Wheel\\\\Event FILES ${SRC_EVENT})
source_group(Wheel\\\\Platform FILES ${SRC_PLATFORM})
source_group(Wheel\\\\ImGui FILES ${SRC_IMGUI})

add_library(Engine STATIC ${WHEEL_SRC})

target_link_libraries(Engine  glfw)
target_link_libraries(Engine  glad)
target_link_libraries(Engine  imgui)

target_precompile_headers(Engine PRIVATE
        <iostream>
        <vector>
        <string>
        <functional>
        <algorithm>
        <memory>
        <sstream>
        "Core/Log.h")