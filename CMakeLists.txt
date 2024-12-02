# -------------------------- GENERAL -------------------------------
cmake_minimum_required(VERSION 3.23)
project(RaycasterGame)

# -------------------------- GLOBAL ---------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static") # not need to copy dll to executable folder


# -------------------------- LIBRARY -------------------------------
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# -------------------------- SOURCE --------------------------------
include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/public
)

file(
        GLOB_RECURSE SOURCES
        LIST_DIRECTORIES true
        CONFIGURE_DEPENDS true
        ${CMAKE_CURRENT_LIST_DIR}/private/*.cpp
)

# -------------------------- TARGETS --------------------------------
add_executable(
        ${CMAKE_PROJECT_NAME}
        ${SOURCES}
)
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        raylib
)


