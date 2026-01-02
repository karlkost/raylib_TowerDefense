#ifndef RAYLIB_TOWERDEFENSE_ENEMY_H
#define RAYLIB_TOWERDEFENSE_ENEMY_H

#include "raylib.h"

struct Enemy {
    Vector2 position; //current position
    Color color; //color of the enemy
    float speed; //how many pixels to move per update
    int size; //size of the square (indicator of health but capped)
    int health; //remaining hit points

    float distanceAlongTrack = 0.0f; //how far the enemy has moved in total
    int currentWaypoint = 0; //waypoint which the enemy has reached

    Enemy(const Vector2 enemyPosition, const Color enemyColor, const float enemySpeed, const int enemySize, const int enemyHealth) :
    position(enemyPosition), color(enemyColor), speed(enemySpeed), size(enemySize), health(enemyHealth)
    {}
};

struct EnemySpawn {
    Enemy enemy;
    float spawnDelay;
};

#endif //RAYLIB_TOWERDEFENSE_ENEMY_H