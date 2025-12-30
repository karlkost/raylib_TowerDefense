#ifndef RAYLIB_TOWERDEFENSE_MAP_H
#define RAYLIB_TOWERDEFENSE_MAP_H

#include "Animation.h"
#include <vector>

struct Map {
    Animation animation; //store the map texture and animation (if it has any, probably not)
    std::vector<Vector2> waypoints; //enemy waypoints for the map
};

#endif //RAYLIB_TOWERDEFENSE_MAP_H