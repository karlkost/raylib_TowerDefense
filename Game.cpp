#include "Game.h"
#include "raymath.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr Vector2 middleOfScreen(screenWidth * 0.5f, screenHeight * 0.5f);

Game::Game() {
    //set up stuff for the player
    startMousePosition = GetMousePosition();
    towerEquipped = false;
    isDragging = false;
}

void Game::run() {
    InitWindow(screenWidth, screenHeight, "");
    SetTargetFPS(60);

    //Initialize game state
    //TODO: temp - remove eventually and add maps in json or txt which has waypoints, waves, and texture stored and load from that
    std::vector<Vector2> waypoints;
    waypoints.push_back(middleOfScreen);
    waypoints.push_back(Vector2Add(middleOfScreen, Vector2(200)));
    waypoints.push_back(Vector2Add(waypoints.at(1), Vector2(0, -200)));
    waypoints.push_back(Vector2Add(waypoints.at(2), Vector2(-200, 0)));

    std::vector<Texture2D> textureList;

    //create tower
    const Texture2D cannonTexture = LoadTexture("textures/raylib_cannon.png");
    const Animation cannonAnimator{cannonTexture, 1, 0};
    Tower cannonTower{cannonAnimator, 50, 1, 1};

    //create enemy
    const Texture2D slimeTexture = LoadTexture("textures/raylib_slime.png");
    const Animation slimeAnimator{slimeTexture, 1, 0};
    Enemy slime{slimeAnimator, waypoints.at(0), 30.0f, 5, waypoints.at(1), 0};

    textureList.push_back(cannonTexture);
    textureList.push_back(slimeTexture);

    float debugTimer = 2.0f;
    float timePassed = 0.0f;

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        timePassed += deltaTime;
        if (timePassed >= debugTimer) {
            enemies.push_back(slime);
            timePassed = 0.0f;
        }


        HandleInput(cannonTower);
        UpdateEnemies(deltaTime, waypoints);
        towerManager.Update(deltaTime, enemies);
        uiManager.Update();

        BeginDrawing();
            ClearBackground(GRAY);

            //debug
            for (const auto& point : waypoints) {
                DrawCircleV(point, 3, GREEN);
            }

            DrawEnemies();
            towerManager.Draw();
            uiManager.Draw();
        EndDrawing();
    }

    for (const auto& t : textureList) {
        UnloadTexture(t);
    }

    CloseWindow();
}

void Game::UpdateEnemies(const float deltaTime, std::vector<Vector2>& waypoints) {
    for (auto& enemy : enemies) {
        //if enemy has reached close to the waypoint, go to the next waypoint
        if (Vector2Equals(enemy.position, enemy.target)) {
            enemy.currentWaypoint++;

            //check if there are more waypoints remaining
            if (enemy.currentWaypoint < waypoints.size()) {
                enemy.target = waypoints.at(enemy.currentWaypoint);
            } else {
                //TODO: player loses health
            }
        } else {
            //move towards next waypoint
            enemy.position = Vector2MoveTowards(enemy.position, enemy.target, enemy.speed * deltaTime);
        }
    }

    std::erase_if(enemies, [waypoints](const Enemy& e){ return e.currentWaypoint >= waypoints.size() || e.health <= 0; });
}

void Game::DrawEnemies() const {
    for (const auto& enemy : enemies) {
        const Rectangle& src = enemy.animation.rect;
        const Rectangle dest = {enemy.position.x, enemy.position.y, src.width, src.height};
        const Vector2 origin = {src.width * 0.5f, src.height * 0.5f};

        DrawTexturePro(enemy.animation.texture, src, dest, origin, 0.0f, WHITE);
    }
}


void Game::HandleInput(Tower& tower) {
    tower.position = GetMousePosition();
    if (uiManager.GetState() == PLACING_TOWER && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) towerManager.PlaceTower(tower);

    towerManager.SelectTowers(uiManager.GetDragArea());
    //delete selected towers
    if (GetKeyPressed() == KEY_BACKSPACE) {
        towerManager.DeleteSelected();
    }
}
