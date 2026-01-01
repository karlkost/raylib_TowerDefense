#include "DebugMap.h"
#include <vector>
#include "raylib.h"
#include "raymath.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 600;
constexpr Vector2 middleOfScreen(screenWidth * 0.5f, screenHeight * 0.5f);

std::vector<Vector2> DebugMap::GetWaypoints() {
    std::vector<Vector2> waypoints;
    waypoints.push_back(Vector2Add(middleOfScreen, Vector2(0, 150)));
    waypoints.push_back(Vector2Add(middleOfScreen, Vector2(150, 150)));
    waypoints.push_back(Vector2Add(waypoints.at(1), Vector2(0, -150)));
    waypoints.push_back(Vector2Add(waypoints.at(2), Vector2(-150, 0)));
    waypoints.push_back(Vector2Add(waypoints.at(3), Vector2(0, -150)));

    return waypoints;
}
