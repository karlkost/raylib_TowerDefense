#ifndef RAYLIB_TOWERDEFENSE_TOWERMANAGER_H
#define RAYLIB_TOWERDEFENSE_TOWERMANAGER_H

#include <memory>
#include <vector>

#include "Enemy.h"
#include "Tower.h"

class TowerManager {
   public:
    void Update(float deltaTime, std::vector<Enemy>& enemies) const;
    void Draw() const;
    void PlaceTower(const std::shared_ptr<Tower>& tower);

    static void DisplayPlacement(const std::shared_ptr<Tower>& tower, bool validPlacement);

   private:
    std::vector<std::unique_ptr<Tower>> m_towers;
};

#endif  // RAYLIB_TOWERDEFENSE_TOWERMANAGER_H