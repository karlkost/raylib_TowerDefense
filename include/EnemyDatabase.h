#ifndef RAYLIB_TOWERDEFENSE_ENEMYDATABASE_H
#define RAYLIB_TOWERDEFENSE_ENEMYDATABASE_H

#include "Enemy.h"

class EnemyDatabase {
   public:
    EnemyDatabase();

    Enemy basic;
    Enemy slow;
    Enemy fast;
};

#endif  // RAYLIB_TOWERDEFENSE_ENEMYDATABASE_H