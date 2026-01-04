#include "TowerManager.h"

#include "ParticleManager.h"

static constexpr Color validRangeColor = {0, 255, 0, 100};
static constexpr Color invalidRangeColor = {255, 0, 0, 100};

void TowerManager::Update(const float deltaTime, std::vector<Enemy>& enemies) const {
    // attacking stuff
    for (const auto& tower : m_towers) {
        tower->UpdateTimeSinceLastAttack(deltaTime);

        if (!tower->CanAttack()) continue;

        for (auto& enemy : enemies) {
            if (tower->EnemyInRange(enemy.position) && enemy.health >= 0) {
                tower->Attack(enemy);
                break;
            }
        }
    }
}

void TowerManager::Draw() const {
    for (const auto& tower : m_towers) {
        tower->Draw();
    }
}

void TowerManager::PlaceTower(const std::shared_ptr<Tower>& tower) { m_towers.push_back(tower->clone()); }

void TowerManager::DisplayPlacement(const std::shared_ptr<Tower>& tower, const bool validPlacement) {
    Vector2 position;
    float range;

    tower->GetPlacementInformation(position, range);
    DrawCircleV(position, range, validPlacement ? validRangeColor : invalidRangeColor);
    tower->Draw();
}