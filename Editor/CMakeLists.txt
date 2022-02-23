cmake_minimum_required(VERSION 3.20)

include_directories(../Engine/Source/Runtime)
include_directories(../Engine/Source/ThirdParty/spdlog/include)
include_directories(../Engine/Source/ThirdParty/ImGui)
include_directories(../Engine/Source/ThirdParty/glm)

add_executable(Editor 
        Source/EditorLayer.h
        Source/EditorLayer.cpp
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
