#include "TowerManager.h"
#include "raymath.h"

static constexpr Color validRangeColor = {0, 255, 0, 100};
static constexpr Color invalidRangeColor = {255, 0, 0, 100};

void TowerManager::Update(const float deltaTime, std::vector<Enemy>& enemies) {
    //attacking stuff
    for (auto& tower : towers) {
        tower.timeSinceAttack += deltaTime;
        if (tower.timeSinceAttack >= tower.attackDelay) {
            //pick a target to attack and attack it
            for (auto& enemy : enemies) {
                //finds the FIRST valid target within range
                //could change to checking collision with circle & rec if enemies will only be rectangles
                const float distanceToEnemy = Vector2Distance(tower.position, enemy.position);
                //check for enemy health incase the update loop hasn't removed the enemy (so two towers don't attack the same target)
                if (distanceToEnemy <= tower.range && enemy.health > 0) {
                    //rotate towards the enemy
                    const Vector2 dir = Vector2Subtract(enemy.position, tower.position);
                    tower.rotation = atan2f(dir.y, dir.x) * RAD2DEG - 90;

                    enemy.health -= tower.damage;
                    tower.timeSinceAttack = 0.0f;

                    tower.animation.currentFrame++;
                    break;
                }
            }
        }
    }
}

void TowerManager::DrawTower(const Tower& tower) {
    const Rectangle& src = tower.animation.rect;
    const Rectangle dest = {tower.position.x, tower.position.y, src.width, src.height};
    const Vector2 origin = {src.width * 0.5f, src.height * 0.5f};

    DrawTexturePro(tower.animation.texture, src, dest, origin, tower.rotation, WHITE);
}

void TowerManager::Draw() const {
    //draw selected circles first so it doesn't cover the tower sprites
    for (const auto& tower : towers) {
        if (tower.selected) {
            DrawCircleV(tower.position, 15, SKYBLUE);
        }
    }

    for (const auto& tower : towers) {
        DrawTower(tower);
    }
}

void TowerManager::DisplayPlacement(const Tower& tower, const bool validPlacement) {
    if (validPlacement) {
        DrawCircleV(tower.position, tower.range, validRangeColor);
    } else {
        DrawCircleV(tower.position, tower.range, invalidRangeColor);
    }

    DrawTower(tower);
}

void TowerManager::PlaceTower(const Tower& tower) {
    towers.push_back(tower);
}

void TowerManager::SelectTowers(const Rectangle& area) {
    for (auto& tower : towers) {
        if (CheckCollisionPointRec(tower.position, area)) {
            tower.selected = true;
        } else {
            tower.selected = false;
        }
    }
}

void TowerManager::DeleteSelected() {
    std::erase_if(towers, [](const Tower& t){ return t.selected; });
}

bool TowerManager::CheckTowerCollisions(const Rectangle& rect) {
    for (const auto& tower : towers) {
        const Rectangle towerHitbox{tower.position.x - tower.animation.rect.width/2, tower.position.y - tower.animation.rect.height/2, tower.animation.rect.width, tower.animation.rect.height};
        if (CheckCollisionRecs(towerHitbox, rect)) {
            return false;
        }
    }

    return true;
}
