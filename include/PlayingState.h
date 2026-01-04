#ifndef RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H
#define RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H

#include "GameState.h"
#include "TowerManager.h"
#include "Enemy.h"
#include <vector>
#include <queue>

class PlayingState : public GameState {
public:
     PlayingState(const std::vector<std::shared_ptr<Tower>>& selectedTowers, const std::vector<Vector2>& mapWaypoints,
          const std::vector<Rectangle>& mapHitboxes, const std::queue<std::queue<EnemySpawn>>& waves);

     void Update(Game& game, float deltaTime) override;
     void Draw() const override;

private:
     std::vector<std::shared_ptr<Tower>> m_selectedTowers; //towers user selected in main menu
     std::queue<std::queue<EnemySpawn>> m_waves;

     TowerManager m_towerManager; //manages towers (shooting, cooldowns, sprites)
     std::queue<EnemySpawn> m_currentWave;
     std::vector<Enemy> m_enemies; //list of enemies on screen

     std::vector<Vector2> m_waypoints; //waypoints in the map which enemies go towards
     std::vector<Rectangle> m_hitboxes; //hitboxes of the waypoints/map to track where towers cant be placed

     std::shared_ptr<Tower> m_equippedTower; //tower to display placement for
     bool m_validTowerPlacement = true;

     float m_startTimer = 0.0f;

     int m_waveNumber = 1;
     float m_timeSinceLastSpawn = 0.0f;

     void SpawnEnemies(float deltaTime);
     void SortEnemies(); //Sort enemies based on how far along the track they are (closest to exit is first)
     void UpdateEnemies(float deltaTime);
     void DrawEnemies() const;
     void HandleInput();
     void EquipTower(const std::shared_ptr<Tower> &tower);
     bool PlacementInBounds(const std::unique_ptr<Tower>& tower) const;
};

#endif //RAYLIB_TOWERDEFENSE_PLAYINGSTATE_H