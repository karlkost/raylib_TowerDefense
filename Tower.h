#ifndef RAYLIB_TOWERDEFENSE_TOWER_H
#define RAYLIB_TOWERDEFENSE_TOWER_H

#include "Animation.h"
#include "raymath.h"

struct Tower {
    //initialized params
    Animation animation; //used for sprite texture & animation
    float range; //how far it can attack
    float attackDelay; //how long to wait before each attack
    int damage;

    //default params
    Vector2 position;
    float timeSinceAttack; //seconds since last attack
    float rotation;
    bool selected; //selected for deletion

    Tower(const Animation &anim, const float r, const float atkDelay, const int dmg) :
    animation(anim), range(r), attackDelay(atkDelay), damage(dmg),
    position(Vector2Zero()), timeSinceAttack(0.0f), rotation(0.0f), selected(false)
    {}
};

#endif //RAYLIB_TOWERDEFENSE_TOWER_H