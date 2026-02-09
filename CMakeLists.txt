cmake_minimum_required(VERSION 3.11)
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

add_executable(raylib_TowerDefense src/main.cpp

 "src/Engine.h" "src/Engine.cpp" "src/UI.h"  
 "src/CameraController.h" "src/Game.h" "src/Game.cpp" "src/Enemy.h"  
 "src/Tower.h" "src/EnemyManager.h" "src/EnemyManager.cpp" "src/TowerManager.h" 
 "src/TowerManager.cpp" "src/Projectile.h" "src/Utils.h")

target_include_directories(raylib_TowerDefense PRIVATE ${raylib_SOURCE_DIR}/src)
target_link_libraries(raylib_TowerDefense PRIVATE raylib)
