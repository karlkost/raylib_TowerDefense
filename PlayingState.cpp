#include "PlayingState.h"

#include <iostream>

static constexpr bool DEBUG_MODE = true;

PlayingState::PlayingState(const std::vector<Tower>& towers) : selectedTowers(towers), equippedTower(selectedTowers.at(0)) {
    towerEquipped = false;
}

void PlayingState::Update(Game&, const float deltaTime) {
    //TODO: spawn enemies

    HandleInput();
    UpdateEnemies(deltaTime);
    towerManager.Update(deltaTime, enemies);
    uiManager.Update();
}

void PlayingState::Draw() const {
    if (DEBUG_MODE) {
        for (const auto& point : waypoints) {
            DrawCircleV(point, 3, GREEN);
        }
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
    //TODO: just use a regular shape as an enemy for simplicity
    for (const auto& enemy : enemies) {
        const Rectangle& src = enemy.animation.rect;
        const Rectangle dest = {enemy.position.x, enemy.position.y, src.width, src.height};
        const Vector2 origin = {src.width * 0.5f, src.height * 0.5f};

        DrawTexturePro(enemy.animation.texture, src, dest, origin, 0.0f, WHITE);
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