cmake_minimum_required(VERSION 4.1.2)
project(raylib_TowerDefense)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
)

FetchContent_MakeAvailable(raylib)

file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})

add_executable(raylib_TowerDefense src/main.cpp
        src/TowerManager.cpp
        src/Game.cpp
        src/PlayingState.cpp
        src/DebugMap.cpp
        src/MainMenuState.cpp
        src/EnemyDatabase.cpp
        src/WaveDatabase.cpp
)

target_include_directories(raylib_TowerDefense PRIVATE include)
target_link_libraries(raylib_TowerDefense PRIVATE raylib)