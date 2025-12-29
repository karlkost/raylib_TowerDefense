#ifndef RAYLIB_FUN_GAME_H
#define RAYLIB_FUN_GAME_H

#include "TowerManager.h"
#include "Enemy.h"
#include "raylib.h"
#include "UIManager.h"

class Game {
    TowerManager towerManager; //manages towers (shooting, cooldowns, sprites)
    UIManager uiManager;
    std::vector<Enemy> enemies; //list of enemies on screen

    Vector2 startMousePosition{}; //mouse position of when the user starts dragging
    bool isDragging; //flag for dragging
    bool towerEquipped; //used to display if the user equipped a tower to show how it would look when placed

    void UpdateEnemies(float deltaTime, std::vector<Vector2>& waypoints);
    void DrawEnemies() const;
    void HandleInput(Tower &tower);
    void CheckValidPlacement(Tower& tower);
public:
    Game();
    void run();
};

#endif //RAYLIB_FUN_GAME_H