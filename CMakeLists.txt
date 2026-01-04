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
        src/TowerManager.cpp
        src/Game.cpp
        src/PlayingState.cpp
        src/DebugMap.cpp
        src/MainMenuState.cpp
        src/EnemyDatabase.cpp
        src/WaveDatabase.cpp
        include/ParticleManager.h
        src/ParticleManager.cpp
        include/DrawCenteredRectangle.h
        include/towers/Cannon.h
        src/towers/Cannon.cpp
)

target_include_directories(raylib_TowerDefense PRIVATE include)
target_link_libraries(raylib_TowerDefense PRIVATE raylib)

add_custom_command(TARGET raylib_TowerDefense POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:raylib_TowerDefense>/textures
)

add_executable(TexturesToCode src/scripts/TexturesToCode.cpp)
target_link_libraries(TexturesToCode PRIVATE raylib)

set(GENERATED_TEXTURES_DIR ${CMAKE_BINARY_DIR}/generated_textures)
set(GENERATED_STAMP ${GENERATED_TEXTURES_DIR}/.generated)

add_custom_command(
    OUTPUT ${GENERATED_STAMP}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_TEXTURES_DIR}
        COMMAND $<TARGET_FILE:TexturesToCode> ${CMAKE_SOURCE_DIR}/textures ${GENERATED_TEXTURES_DIR}
    COMMAND ${CMAKE_COMMAND} -E touch ${GENERATED_STAMP}
    DEPENDS TexturesToCode
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating texture headers into ${GENERATED_TEXTURES_DIR}"
)

add_custom_target(generate_textures DEPENDS ${GENERATED_STAMP})

add_dependencies(raylib_TowerDefense generate_textures)

target_include_directories(raylib_TowerDefense PRIVATE ${GENERATED_TEXTURES_DIR})
