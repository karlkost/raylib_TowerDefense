#ifndef RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H
#define RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H

#include "GameState.h"
#include "TowerManager.h"
#include "UIManager.h"
#include "Enemy.h"
#include <vector>

class PlayingState : public GameState {
     std::vector<Tower> selectedTowers; //towers user selected in main menu

     TowerManager towerManager; //manages towers (shooting, cooldowns, sprites)
     UIManager uiManager; //manages ui (text on screen)
     std::vector<Enemy> enemies; //list of enemies on screen
     std::vector<Vector2> waypoints;

     Tower equippedTower;
     bool towerEquipped = false;

     void UpdateEnemies(float deltaTime);
     void DrawEnemies() const;
     void HandleInput();
public:
     PlayingState(const std::vector<Tower>& towers);

     void Update(Game& game, float deltaTime) override;
     void Draw() const override;
};

#endif //RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H