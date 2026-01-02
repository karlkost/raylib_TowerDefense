#include "Game.h"
#include "MainMenuState.h"
#include "WaveDatabase.h"
#include <vector>
#include "raylib.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

void Game::run() {
    InitWindow(screenWidth, screenHeight, "");
    SetTargetFPS(60);

    //Camera2D camera{Vector2Zero(), Vector2Zero(), 0.0f, 1.0f};

    std::vector<Texture2D> textureList;
    //load all textures
    const Texture2D cannonTowerTexture = LoadTexture("textures/raylib_cannon.png");
    const Animation cannonTowerAnimator{cannonTowerTexture, 1, 0};
    Tower cannonTower{cannonTowerAnimator, 50, 1, 1};

    //const Texture2D cannonBallTexture = LoadTexture("textures/raylib_cannon_ball.png");
    //const Animation cannonBallAnimator{cannonBallTexture, 4, 8};

    textureList.push_back(cannonTowerTexture);

    std::vector<Tower> loadedTowers;
    loadedTowers.push_back(cannonTower);

    WaveDatabase::LoadWaves();

    this->ChangeState(std::make_unique<MainMenuState>(loadedTowers));

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        currentState->Update(*this, deltaTime);

        BeginDrawing();
            ClearBackground(GRAY);
            currentState->Draw();

        EndDrawing();
    }

    for (const auto& t : textureList) {
        UnloadTexture(t);
    }

    CloseWindow();
}

void Game::ChangeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}
