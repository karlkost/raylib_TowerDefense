#include "MainMenuState.h"
#include "Game.h"
#include "PlayingState.h"
#include "DebugMap.h"
#include "WaveDatabase.h"

#include <iostream>


static constexpr float PATH_SIZE = 30.0f;

void MainMenuState::Update(Game& game, const float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), m_playButton)) {
            //for debugging
            const std::vector<Vector2> waypoints = DebugMap::GetWaypoints();

            //create rect hitboxes so towers don't interfere with waypoints
            std::vector<Rectangle> mapHitboxes;
            for (int i = 0; i < waypoints.size() - 1; i++) {
                const Vector2 waypoint1 = waypoints.at(i);
                const Vector2 waypoint2 = waypoints.at(i + 1);

                float x = std::min(waypoint1.x, waypoint2.x) - PATH_SIZE / 2;
                float y = std::min(waypoint1.y, waypoint2.y) - PATH_SIZE / 2;
                float width  = std::abs(waypoint2.x - waypoint1.x) + PATH_SIZE;
                float height = std::abs(waypoint2.y - waypoint1.y) + PATH_SIZE;

                Rectangle enemyPath = { x, y, width, height };
                mapHitboxes.push_back(enemyPath);
            }

            game.ChangeState(std::make_unique<PlayingState>(m_towers, waypoints, mapHitboxes, WaveDatabase::waves));
        }
    }
}

void MainMenuState::Draw() const {
    DrawText("TOWER DEFENSE GAME", 300, 200, 30, BLACK);
    DrawRectangleRec(m_playButton, BLACK);
    DrawText("PLAY", 350, 350, 30, WHITE);
}