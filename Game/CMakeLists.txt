cmake_minimum_required(VERSION 3.20)

include_directories(../Engine/Source/Runtime)
include_directories(../Engine/Source/ThirdParty/spdlog/include)
include_directories(../Engine/Source/ThirdParty/ImGui)
include_directories(../Engine/Source/ThirdParty/glm)

add_executable(Game 
        Source/Sandbox2DLayer.h
        Source/Sandbox2DLayer.cpp
        Source/main.cpp)

target_link_libraries(Game Engine)

target_precompile_headers(Game PRIVATE
        <iostream>
        <vector>
        <string>
        <functional>
        <algorithm>
        <memory>
        <sstream>)
