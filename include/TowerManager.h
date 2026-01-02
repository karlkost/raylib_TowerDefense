#ifndef RAYLIB_TOWERDEFENSE_TOWERMANAGER_H
#define RAYLIB_TOWERDEFENSE_TOWERMANAGER_H

#include "Tower.h"
#include "Enemy.h"
#include <vector>
#include "raylib.h"

class TowerManager {
public:
    TowerManager() = default;
    void Update(float deltaTime, std::vector<Enemy>& enemies);
    void Draw() const;
    static void DisplayPlacement(const Tower& tower, bool validPlacement);
    static void DrawTower(const Tower& tower);
    void PlaceTower(const Tower& tower);
    void SelectTowers(const Rectangle& area);
    void DeleteSelected();
    bool CheckTowerCollisions(const Rectangle& rect);

private:
    std::vector<Tower> m_towers;
};

#endif //RAYLIB_TOWERDEFENSE_TOWERMANAGER_H