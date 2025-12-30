#ifndef RAYLIB_FUN_ENEMY_H
#define RAYLIB_FUN_ENEMY_H

#include "raylib.h"

struct Enemy {
    Vector2 position; //current position
    Vector2 size; //size of enemy
    Color color; //color of the enemy

    float speed; //how many pixels to move per update
    int health; //hit points

    Vector2 target; //target position/waypoint to go towards
    int currentWaypoint; //waypoint which the enemy has reached
};

#endif //RAYLIB_FUN_ENEMY_H