#ifndef RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H
#define RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H

#include "GameState.h"
#include "TowerManager.h"
#include "Enemy.h"
#include <vector>
#include <queue>

class PlayingState : public GameState {
     std::vector<Tower> selectedTowers; //towers user selected in main menu
     std::queue<std::queue<EnemySpawn>> waves;

     TowerManager towerManager; //manages towers (shooting, cooldowns, sprites)
     std::queue<EnemySpawn> currentWave;
     std::vector<Enemy> enemies; //list of enemies on screen

     std::vector<Vector2> waypoints; //waypoints in the map which enemies go towards
     std::vector<Rectangle> hitboxes; //hitboxes of the waypoints/map to track where towers cant be placed

     Tower equippedTower;
     bool towerEquipped = false;
     bool validTowerPlacement = true;

     float startTimer = 0.0f;

     int waveNumber = 1;
     float timeSinceLastSpawn = 0.0f;

     void SpawnEnemies(float deltaTime);
     void UpdateEnemies(float deltaTime);
     void DrawEnemies() const;
     void HandleInput();
     void EquipTower(const Tower& tower);
     bool PlacementInBounds(const Tower &tower);
public:
     PlayingState(const std::vector<Tower>& towers, const std::vector<Vector2>& mapWaypoints,
          const std::vector<Rectangle>& mapHitboxes, const std::queue<std::queue<EnemySpawn>>& mapWaves);

     void Update(Game& game, float deltaTime) override;
     void Draw() const override;
};

#endif //RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H