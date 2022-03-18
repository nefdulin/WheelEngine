cmake_minimum_required(VERSION 3.20)

include_directories(../Engine/Source/Runtime)
include_directories(../Engine/Source/ThirdParty/spdlog/include)
include_directories(../Engine/Source/ThirdParty/ImGui)
include_directories(../Engine/Source/ThirdParty/glm)
include_directories(../Engine/Source/ThirdParty/entt/single_include)
include_directories(../Engine/Source/ThirdParty/ImGuizmo)

add_executable(Editor 
        Source/EditorLayer.h
        Source/EditorLayer.cpp
        Source/EditorCamera.h
        Source/EditorCamera.cpp
        Source/Panels/SceneHierarchyPanel.h
        Source/Panels/SceneHierarchyPanel.cpp
        Source/Panels/SceneInspectorPanel.h
        Source/Panels/SceneInspectorPanel.cpp
        Source/main.cpp)

target_link_libraries(Editor Engine)

target_precompile_headers(Editor PRIVATE
        <iostream>
        <vector>
        <string>
        <functional>
        <algorithm>
        <memory>
        <sstream>)
