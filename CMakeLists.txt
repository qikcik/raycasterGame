cmake_minimum_required(VERSION 3.28)
project(GameRaycaster)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static") # not need to copy dll to executable folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

#IMPORT
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG fdc084f532189fda8474079f79e74fa5e3541c9f) # v1.90.5
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

add_library(
        imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp)
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})

FetchContent_Declare(
        rlImGui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui
        GIT_TAG 3c6986358c001851d9bc20e55acf9de803c73b5d)
FetchContent_MakeAvailable(rlImGui)
FetchContent_GetProperties(rlImGui SOURCE_DIR RLIMGUI_DIR)
add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
target_link_libraries(rlimgui PRIVATE imgui raylib)
target_include_directories(rlimgui INTERFACE ${rlimgui_SOURCE_DIR})


#SOURCE
include_directories(${CMAKE_CURRENT_LIST_DIR}/source)

file(
        GLOB_RECURSE SOURCES LIST_DIRECTORIES true
        ${CMAKE_CURRENT_LIST_DIR}/source/*/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/source/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/source/*/*.hpp
)


#TARGET
add_executable(
        GameRaycaster
        ${CMAKE_CURRENT_LIST_DIR}/source/main.cpp
        ${SOURCES}
)
target_link_libraries(
        GameRaycaster
        imgui
        raylib
        rlimgui
)
