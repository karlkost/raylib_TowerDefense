#include "PlayingState.h"

#include <iostream>


PlayingState::PlayingState(const std::vector<Tower>& towers, const std::vector<Vector2>& mapWaypoints)
: selectedTowers(towers), waypoints(mapWaypoints), equippedTower(selectedTowers.at(0)) {
    towerEquipped = false;
}


void PlayingState::Update(Game&, const float deltaTime) {
    //TODO: spawn enemies in waves
    debugTimer += deltaTime;
    if (debugTimer >= 2.0f) {
        const Enemy basicEnemy{waypoints.at(0), Vector2{10,10}, BLUE, 30, 5, waypoints.at(0), 0};
        debugTimer = 0.0f;
        enemies.push_back(basicEnemy);
    }


    HandleInput();
    UpdateEnemies(deltaTime);
    towerManager.Update(deltaTime, enemies);
    uiManager.Update();
}

void PlayingState::Draw() const {
    for (const auto& point : waypoints) {
        DrawCircleV(point, 3, GREEN);
    }


    DrawEnemies();
    towerManager.Draw();
    uiManager.Draw();
}

void PlayingState::UpdateEnemies(const float deltaTime) {
    for (auto& enemy : enemies) {
        //if enemy has reached close to the waypoint, set target to the next waypoint
        if (Vector2Equals(enemy.position, enemy.target)) {
            enemy.currentWaypoint++;

            //check if there are more waypoints remaining
            if (enemy.currentWaypoint < waypoints.size()) {
                enemy.target = waypoints.at(enemy.currentWaypoint);
            } else {
                //TODO: player loses health
            }
        } else {
            //move towards next waypoint
            enemy.position = Vector2MoveTowards(enemy.position, enemy.target, enemy.speed * deltaTime);
        }
    }

    std::erase_if(enemies, [this](const Enemy& e){ return e.currentWaypoint >= waypoints.size() || e.health <= 0; });
}

void PlayingState::DrawEnemies() const {
    for (const auto& enemy : enemies) {
        const float center = enemy.size.x/2;
        Vector2 drawPosition = {enemy.position.x - center, enemy.position.y - center};
        DrawRectangleV(drawPosition, enemy.size, enemy.color);
    }
}

void PlayingState::HandleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        equippedTower = selectedTowers.at(0);
        uiManager.EquipTower(equippedTower);
        towerEquipped = !towerEquipped;
    }

    if (towerEquipped && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        equippedTower.position = GetMousePosition();
        towerManager.PlaceTower(equippedTower);
    }
}