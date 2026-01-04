#include "PlayingState.h"
#include "ParticleManager.h"
#include "DrawCenteredRectangle.h"
#include <algorithm>
#include <ranges>
#include "raymath.h"

PlayingState::PlayingState(const std::vector<std::shared_ptr<Tower>>& selectedTowers, const std::vector<Vector2>& mapWaypoints,
                           const std::vector<Rectangle>& mapHitboxes, const std::queue<std::queue<EnemySpawn>>& waves)
: m_selectedTowers(selectedTowers), m_waves(waves), m_waypoints(mapWaypoints), m_hitboxes(mapHitboxes)
{}

void PlayingState::Update(Game&, const float deltaTime) {
    //wait 10 seconds to give the player time to prepare
    if (m_startTimer >= 1.0f) {
        if (!m_waves.empty() && m_currentWave.empty() && m_enemies.empty()) {
            m_currentWave = m_waves.front();
            m_waves.pop();
        }

        //check if current wave still has enemies
        if (!m_currentWave.empty()) {
            //spawn an enemy if it has more
            SpawnEnemies(deltaTime);
        } else if (m_waves.empty()) {
            //game is won
        }

    } else {
        m_startTimer += deltaTime;
    }

    HandleInput();
    UpdateEnemies(deltaTime);
    SortEnemies();
    m_towerManager.Update(deltaTime, m_enemies);
    ParticleManager::GetInstance().Update(deltaTime);
    if (m_equippedTower) {
        m_equippedTower->SetPosition(GetMousePosition());
        m_validTowerPlacement = true;//PlacementInBounds(m_equippedTower);
    }
}

void PlayingState::Draw() const {
    // for (const auto& point : m_waypoints) {
    //     DrawCircleV(point, 3, GREEN);
    // }

    for (const auto& rect : m_hitboxes) {
        DrawRectangleRec(rect, Color{5,50,100,255});
    }

    DrawEnemies();
    m_towerManager.Draw();
    ParticleManager::GetInstance().Draw();
    if (m_equippedTower) {
        TowerManager::DisplayPlacement(m_equippedTower, m_validTowerPlacement);
    }
}

void PlayingState::SpawnEnemies(const float deltaTime) {
    m_timeSinceLastSpawn += deltaTime;

    EnemySpawn& es = m_currentWave.front();
    if (m_timeSinceLastSpawn >= es.spawnDelay) {
        m_timeSinceLastSpawn = 0.0f;
        m_currentWave.pop();

        Enemy e = es.enemy;
        e.position = m_waypoints.front();

        m_enemies.push_back(e);
    }
}

void PlayingState::SortEnemies() {
    std::ranges::sort(m_enemies, [](const Enemy& a, const Enemy& b) {
        return a.distanceAlongPath > b.distanceAlongPath;
    });
}

void PlayingState::UpdateEnemies(const float deltaTime) {
    for (auto& enemy : m_enemies) {
        //if enemy has reached close to the waypoint, set target to the next waypoint
        const Vector2& enemyTarget = m_waypoints.at(enemy.currentWaypoint);
        if (Vector2Equals(enemy.position, enemyTarget)) {
            enemy.currentWaypoint++;

            //check if there are more waypoints remaining
            if (enemy.currentWaypoint >= m_waypoints.size()) {
                //TODO: player loses health
            }
        } else {
            //move towards next waypoint
            const Vector2 nextPosition = Vector2MoveTowards(enemy.position, enemyTarget, enemy.speed * deltaTime);
            enemy.position = nextPosition;
            enemy.distanceAlongPath += Vector2LengthSqr(nextPosition);
        }
    }

    std::erase_if(m_enemies, [this](const Enemy& e){ return e.currentWaypoint >= m_waypoints.size() || e.health <= 0; });
}

void PlayingState::DrawEnemies() const {
    for (const auto& enemy : m_enemies) {
        DrawCenteredRectangle(enemy);
    }
}

void PlayingState::HandleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        EquipTower(m_selectedTowers.at(0));
    }

    if (m_equippedTower && m_validTowerPlacement && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        m_equippedTower->SetPosition(GetMousePosition());
        m_towerManager.PlaceTower(m_equippedTower);
    }
}

void PlayingState::EquipTower(const std::shared_ptr<Tower>& tower) {
    if (m_equippedTower) {
        m_equippedTower = nullptr;
        ShowCursor();
    } else {
        m_equippedTower = tower;
        HideCursor();
    }
}

// bool PlayingState::PlacementInBounds(const Tower& tower) const {
//     const auto towerHitbox = tower.getHitbox();
//
//     //check path hitboxes
//     for (const auto& rect : m_hitboxes) {
//         if (CheckCollisionCircleRec(rect, towerHitbox)) {
//             return false;
//         }
//     }
//
//     //check placed tower hitboxes
//     return m_towerManager.CheckTowerCollisions(towerHitbox);
// }