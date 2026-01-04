#ifndef RAYLIB_TOWERDEFENSE_TOWERMANAGER_H
#define RAYLIB_TOWERDEFENSE_TOWERMANAGER_H


#include "Tower.h"
#include "Enemy.h"
#include <vector>
#include <memory>

class TowerManager {
public:
    void Update(float deltaTime, std::vector<Enemy>& enemies) const;
    void Draw() const;
    void PlaceTower(const std::shared_ptr<Tower> &tower);

    static void DisplayPlacement(const std::shared_ptr<Tower>& tower, bool validPlacement) ;
private:
    std::vector<std::unique_ptr<Tower>> m_towers;
};

#endif //RAYLIB_TOWERDEFENSE_TOWERMANAGER_H