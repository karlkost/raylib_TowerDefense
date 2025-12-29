#ifndef RAYLIB_FUN_ENEMY_H
#define RAYLIB_FUN_ENEMY_H

#include "Animation.h"
#include "raylib.h"

struct Enemy {
    Animation animation;
    Vector2 position; //current position
    float speed; //how many pixels to move per update
    int health; //hit points

    Vector2 target; //target position/waypoint to go towards
    int currentWaypoint; //waypoint which the enemy has reached
};

#endif //RAYLIB_FUN_ENEMY_H