#ifndef RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H
#define RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H

#include "GameState.h"
#include "TowerManager.h"
#include "Enemy.h"
#include <vector>
#include <queue>

class PlayingState : public GameState {
     std::vector<Tower> m_selectedTowers; //towers user selected in main menu
     std::queue<std::queue<EnemySpawn>> m_waves;

     TowerManager m_towerManager; //manages towers (shooting, cooldowns, sprites)
     std::queue<EnemySpawn> m_currentWave;
     std::vector<Enemy> m_enemies; //list of enemies on screen

     std::vector<Vector2> m_waypoints; //waypoints in the map which enemies go towards
     std::vector<Rectangle> m_hitboxes; //hitboxes of the waypoints/map to track where towers cant be placed

     Tower m_equippedTower;
     bool m_towerEquipped = false;
     bool m_validTowerPlacement = true;

     float m_startTimer = 0.0f;

     int m_waveNumber = 1;
     float m_timeSinceLastSpawn = 0.0f;

     void SpawnEnemies(float deltaTime);
     void SortEnemies();
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