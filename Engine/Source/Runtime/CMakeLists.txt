cmake_minimum_required(VERSION 3.20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../ThirdParty/spdlog/include)
include_directories(../ThirdParty/glfw/include)
include_directories(../ThirdParty/glad/include)
include_directories(../ThirdParty/ImGui)
include_directories(../ThirdParty/glm)
include_directories(../ThirdParty/stb_image)
include_directories(../ThirdParty/entt/single_include)
include_directories(../ThirdParty/imguizmo)
include_directories(../ThirdParty/assimp)

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
        Renderer/RendererAPI.h
        Renderer/RendererAPI.cpp
        Renderer/Renderer2D.h
        Renderer/Renderer2D.cpp
        Renderer/RenderCommand.h
        Renderer/RenderCommand.cpp
        Renderer/Shader.h
        Renderer/Shader.cpp
        Renderer/VertexArray.h
        Renderer/VertexArray.cpp
        Renderer/Framebuffer.h
        Renderer/Framebuffer.cpp
        Renderer/Buffer.h
        Renderer/Buffer.cpp
        Renderer/Camera.h
        Renderer/Texture.h
        Renderer/Texture.cpp
        Renderer/OrthographicCamera.cpp
        Renderer/OrthographicCamera.h
        Renderer/Model.h
        Renderer/Model.cpp
        Renderer/Mesh.h
        Renderer/Mesh.cpp)

set(SRC_PLATFORM_MAC
        Platform/Mac/MacWindow.h
        Platform/Mac/MacWindow.cpp
        Platform/Mac/MacInput.cpp)

set(SRC_PLATFORM_OPENGL
        Platform/OpenGL/OpenGLContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLVertexArray.h
        Platform/OpenGL/OpenGLVertexArray.cpp
        Platform/OpenGL/OpenGLRendererAPI.h
        Platform/OpenGL/OpenGLRendererAPI.cpp
        Platform/OpenGL/OpenGLBuffer.h
        Platform/OpenGL/OpenGLBuffer.cpp
        Platform/OpenGL/OpenGLShader.h
        Platform/OpenGL/OpenGLShader.cpp
        Platform/OpenGL/OpenGLTexture2D.h
        Platform/OpenGL/OpenGLTexture2D.cpp
        Platform/OpenGL/OpenGLFrameBuffer.h
        Platform/OpenGL/OpenGLFrameBuffer.cpp)

set(SRC_IMGUI
        ImGui/ImGuiBuild.cpp
        ImGui/ImGuiLayer.h
        ImGui/ImGuiLayer.cpp)

set(SRC_SCENE
        Scene/Components.h
        Scene/Scene.h
        Scene/Entity.h
        Scene/ScriptableEntity.h
        Scene/SceneCamera.h
        Scene/Scene.cpp
        Scene/Entity.cpp
        Scene/SceneCamera.cpp)

set(WHEEL_SRC
        ${SRC_CORE}
        ${SRC_EVENT}
        ${SRC_RENDERER}
        ${SRC_PLATFORM_MAC}
        ${SRC_PLATFORM_OPENGL}
        ${SRC_IMGUI}
        ${SRC_SCENE})

source_group(Wheel\\\\Core FILES ${SRC_CORE})
source_group(Wheel\\\\Event FILES ${SRC_EVENT})
source_group(Wheel\\\\Platform\\\\Mac FILES ${SRC_PLATFORM_MAC})
source_group(Wheel\\\\Platform\\\\OpenGL FILES ${SRC_PLATFORM_OPENGL})
source_group(Wheel\\\\ImGui FILES ${SRC_IMGUI})
source_group(Wheel\\\\Renderer FILES ${SRC_RENDERER})

add_library(Engine STATIC ${WHEEL_SRC})

target_link_libraries(Engine  glfw)
target_link_libraries(Engine  glad)
target_link_libraries(Engine  imgui)
target_link_libraries(Engine  stb_image)
target_link_libraries(Engine  imguizmo)
target_link_libraries(Engine  assimp)

target_precompile_headers(Engine PRIVATE
        <iostream>
        <vector>
        <string>
        <functional>
        <algorithm>
        <array>
        <memory>
        <sstream>
        <unordered_map>
        "Core/Log.h"
        "Core/Core.h")