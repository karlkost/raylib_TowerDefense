#include "PlayingState.h"
#include <algorithm>
#include <ranges>

PlayingState::PlayingState(const std::vector<Tower>& towers, const std::vector<Vector2>& mapWaypoints,
                           const std::vector<Rectangle>& mapHitboxes, const std::queue<std::queue<EnemySpawn>>& mapWaves)
: m_selectedTowers(towers), m_waypoints(mapWaypoints), m_hitboxes(mapHitboxes), m_equippedTower(m_selectedTowers.at(0)), m_waves(mapWaves)
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
    if (m_towerEquipped) {
        m_equippedTower.position = GetMousePosition();
        m_validTowerPlacement = PlacementInBounds(m_equippedTower);
    }
}

void PlayingState::Draw() const {
    for (const auto& point : m_waypoints) {
        DrawCircleV(point, 3, GREEN);
    }

    for (const auto& rect : m_hitboxes) {
        DrawRectangleRec(rect, Color{5,50,100,255});
    }

    DrawEnemies();
    m_towerManager.Draw();
    if (m_towerEquipped) {
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
        return a.distanceAlongTrack > b.distanceAlongTrack;
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
            enemy.distanceAlongTrack += Vector2LengthSqr(nextPosition);
        }
    }

    std::erase_if(m_enemies, [this](const Enemy& e){ return e.currentWaypoint >= m_waypoints.size() || e.health <= 0; });
}

void PlayingState::DrawEnemies() const {
    for (const auto& enemy : m_enemies) {
        const auto enemySize = static_cast<float>(enemy.size);

        //rectangles draw from top left so we need to calculate the center and then use that as the position vector in RectangleV so it looks centered
        const float center = enemySize/2;
        const Vector2 drawPosition = {enemy.position.x - center, enemy.position.y - center};

        DrawRectangleV(drawPosition, (Vector2){enemySize, enemySize}, enemy.color);
    }
}

void PlayingState::HandleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        EquipTower(m_selectedTowers.at(0));
    }

    if (m_towerEquipped && m_validTowerPlacement && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        m_equippedTower.position = GetMousePosition();
        m_towerManager.PlaceTower(m_equippedTower);
    }
}

void PlayingState::EquipTower(const Tower& tower) {
    m_equippedTower = tower;
    m_towerEquipped = !m_towerEquipped;

    if (m_towerEquipped) {
        HideCursor();
    } else {
        ShowCursor();
    }
}

bool PlayingState::PlacementInBounds(const Tower& tower) {
    const Rectangle towerHitbox = {tower.position.x - tower.animation.rect.width/2, tower.position.y - tower.animation.rect.height/2,
        tower.animation.rect.width, tower.animation.rect.height};

    //check path hitboxes
    for (const auto& rect : m_hitboxes) {
        if (CheckCollisionRecs(rect, towerHitbox)) {
            return false;
        }
    }

    //check placed tower hitboxes
    return m_towerManager.CheckTowerCollisions(towerHitbox);
}