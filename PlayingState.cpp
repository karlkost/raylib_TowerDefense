#include "PlayingState.h"

#include <algorithm>
#include <ranges>
#include <iostream>

PlayingState::PlayingState(const std::vector<Tower>& towers, const std::vector<Vector2>& mapWaypoints,
                           const std::vector<Rectangle>& mapHitboxes, const std::queue<std::queue<EnemySpawn>>& mapWaves)
: selectedTowers(towers), waypoints(mapWaypoints), hitboxes(mapHitboxes), equippedTower(selectedTowers.at(0)), waves(mapWaves)
{}

void PlayingState::Update(Game&, const float deltaTime) {
    //wait 10 seconds to give the player time to prepare
    if (startTimer >= 1.0f) {
        if (!waves.empty() && currentWave.empty() && enemies.empty()) {
            currentWave = waves.front();
            waves.pop();
        }

        //check if current wave still has enemies
        if (!currentWave.empty()) {
            //spawn an enemy if it has more
            SpawnEnemies(deltaTime);
        } else if (waves.empty()) {
            //game is won
        }

    } else {
        startTimer += deltaTime;
    }

    HandleInput();
    UpdateEnemies(deltaTime);
    SortEnemies();
    towerManager.Update(deltaTime, enemies);
    if (towerEquipped) {
        equippedTower.position = GetMousePosition();
        validTowerPlacement = PlacementInBounds(equippedTower);
    }
}

void PlayingState::Draw() const {
    for (const auto& point : waypoints) {
        DrawCircleV(point, 3, GREEN);
    }

    for (const auto& rect : hitboxes) {
        DrawRectangleRec(rect, Color{5,50,100,255});
    }

    DrawEnemies();
    towerManager.Draw();
    if (towerEquipped) {
        TowerManager::DisplayPlacement(equippedTower, validTowerPlacement);
    }
}

void PlayingState::SpawnEnemies(const float deltaTime) {
    timeSinceLastSpawn += deltaTime;

    EnemySpawn& es = currentWave.front();
    if (timeSinceLastSpawn >= es.spawnDelay) {
        timeSinceLastSpawn = 0.0f;
        currentWave.pop();

        Enemy e = es.enemy;
        e.position = waypoints.front();
        e.target = waypoints.front();

        enemies.push_back(e);
    }
}

void PlayingState::SortEnemies() {
    std::vector<std::vector<Enemy>> enemiesByWaypoints{waypoints.size()};

    //store enemies by waypoints
    for (auto& e : enemies) {
        enemiesByWaypoints.at(e.currentWaypoint).push_back(e);
    }

    //sort enemies in their waypoint groups by how close they are to their next waypoint
    for (auto& group : enemiesByWaypoints) {
        std::ranges::sort(group, [](const Enemy& a, const Enemy& b) {
           return Vector2DistanceSqr(a.position, a.target) < Vector2DistanceSqr(b.position, b.target);
        });
    }

    enemies.clear();
    //add the enemies back into the list based on waypoint (descending)
    for (auto& group : enemiesByWaypoints | std::views::reverse) {
        enemies.insert(enemies.end(), group.begin(), group.end());
    }
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
        //rectangles draw from top left so we need to calculate the center and then use that as the position vector in RectangleV so it looks centered
        const float center = enemy.size.x/2;
        const Vector2 drawPosition = {enemy.position.x - center, enemy.position.y - center};
        DrawRectangleV(drawPosition, enemy.size, enemy.color);
    }
}

void PlayingState::HandleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        EquipTower(selectedTowers.at(0));
    }

    if (towerEquipped && validTowerPlacement && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        equippedTower.position = GetMousePosition();
        towerManager.PlaceTower(equippedTower);
    }
}

void PlayingState::EquipTower(const Tower& tower) {
    equippedTower = tower;
    towerEquipped = !towerEquipped;

    if (towerEquipped) {
        HideCursor();
    } else {
        ShowCursor();
    }
}

bool PlayingState::PlacementInBounds(const Tower& tower) {
    const Rectangle towerHitbox = {tower.position.x - tower.animation.rect.width/2, tower.position.y - tower.animation.rect.height/2,
        tower.animation.rect.width, tower.animation.rect.height};

    //check path hitboxes
    for (const auto& rect : hitboxes) {
        if (CheckCollisionRecs(rect, towerHitbox)) {
            return false;
        }
    }

    //check placed tower hitboxes
    return towerManager.CheckTowerCollisions(towerHitbox);
}