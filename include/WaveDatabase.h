#ifndef RAYLIB_TOWERDEFENSE_WAVEDATABASE_H
#define RAYLIB_TOWERDEFENSE_WAVEDATABASE_H

#include "Enemy.h"
#include <queue>

class WaveDatabase {
public:
    static std::queue<std::queue<EnemySpawn>> waves;

    static void LoadWaves();
};

#endif //RAYLIB_TOWERDEFENSE_WAVEDATABASE_H