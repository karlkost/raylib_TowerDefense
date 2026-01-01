#ifndef RAYLIB_TOWERDEFENSE_ENEMY_H
#define RAYLIB_TOWERDEFENSE_ENEMY_H

#include "raylib.h"

struct Enemy {
    Vector2 position; //current position
    Vector2 size; //size of enemy
    Color color; //color of the enemy

    float speed; //how many pixels to move per update
    int health; //hit points

    Vector2 target; //target position/waypoint to go towards
    int currentWaypoint; //waypoint which the enemy has reached

    Enemy(const Vector2 enemyPosition, const Vector2 enemySize, const Color enemyColor, const float enemySpeed, const int enemyHealth) :
    position(enemyPosition), size(enemySize), color(enemyColor), speed(enemySpeed), health(enemyHealth),
    target(enemyPosition), currentWaypoint(0)
    {}
};

#endif //RAYLIB_TOWERDEFENSE_ENEMY_H