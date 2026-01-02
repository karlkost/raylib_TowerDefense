#ifndef RAYLIB_TOWERDEFENSE_DEBUGMAP_H
#define RAYLIB_TOWERDEFENSE_DEBUGMAP_H

#include <vector>
#include "raylib.h"

class DebugMap {
public:
    static std::vector<Vector2> GetWaypoints();
};

#endif //RAYLIB_TOWERDEFENSE_DEBUGMAP_H