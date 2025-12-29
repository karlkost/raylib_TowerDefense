#ifndef RAYLIB_FUN_TOWERMANAGER_H
#define RAYLIB_FUN_TOWERMANAGER_H

#include "Enemy.h"
#include "Animation.h"
#include <vector>
#include "raylib.h"
#include "raymath.h"

struct Tower {
    Animation animation; //used for sprite/animation
    float range; //how far it can attack
    float attackDelay; //how long to wait before each attack
    int damage;

    Vector2 position;
    float timeSinceAttack; //seconds since last attack
    float rotation;
    bool selected; //selected for deletion

    Tower(const Animation &anim, const float r, const float atkDelay, const int dmg) :
    animation(anim), range(r), attackDelay(atkDelay), damage(dmg),
    position(Vector2Zero()), timeSinceAttack(0.0f), rotation(0.0f), selected(false)
    {}
};

class TowerManager {
    std::vector<Tower> towers;

public:
    TowerManager() = default;
    void Update(float deltaTime, std::vector<Enemy>& enemies);
    void Draw() const;
    static void DisplayPlacement(const Tower& tower, bool validPlacement);
    void PlaceTower(const Tower& tower);
    void SelectTowers(const Rectangle& area);
    void DeleteSelected();
};

#endif //RAYLIB_FUN_TOWERMANAGER_H