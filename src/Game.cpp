#include "Game.h"

#include <vector>

#include "MainMenuState.h"
#include "WaveDatabase.h"
#include "raylib.h"
#include "towers/Cannon.h"
#include "textures/raylib_cannon.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

void Game::run() {
    InitWindow(screenWidth, screenHeight, "");
    SetTargetFPS(60);

    // Camera2D camera{Vector2Zero(), Vector2Zero(), 0.0f, 1.0f};

    std::vector<Texture2D> textureList;

    const Image cannonTowerImage = { RAYLIB_CANNON_DATA, RAYLIB_CANNON_WIDTH, RAYLIB_CANNON_HEIGHT, 1, RAYLIB_CANNON_FORMAT };
    Texture2D cannonTowerTexture = LoadTextureFromImage(cannonTowerImage);

    // const Texture2D cannonBallTexture = LoadTexture("textures/raylib_cannon_ball.png");
    // const Animation cannonBallAnimator{cannonBallTexture, 4, 8};

    textureList.push_back(cannonTowerTexture);

    std::vector<std::shared_ptr<Tower>> loadedTowers;
    loadedTowers.push_back(std::make_shared<Cannon>(cannonTowerTexture));

    WaveDatabase::LoadWaves();

    this->ChangeState(std::make_unique<MainMenuState>(loadedTowers));

    while (!WindowShouldClose()) {
        const float deltaTime = GetFrameTime();

        m_currentState->Update(*this, deltaTime);

        BeginDrawing();
        ClearBackground(GRAY);
        m_currentState->Draw();

        EndDrawing();
    }

    for (const auto& t : textureList) {
        UnloadTexture(t);
    }

    CloseWindow();
}

void Game::ChangeState(std::unique_ptr<GameState> newState) { m_currentState = std::move(newState); }
