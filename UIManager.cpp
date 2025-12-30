#include "UIManager.h"
#include <string>

UIManager::UIManager() :
playerCoins(0), playerLifeCount(0), waveNumber(0)
{}

void UIManager::Update() {
    if (equippedTower.has_value()) equippedTower.value().position = GetMousePosition();
}

void UIManager::Draw() const {
    //draw UI
    if (equippedTower.has_value()) TowerManager::DisplayPlacement(equippedTower.value(), true);

    //draw text
    DrawText(("Coins: " + std::to_string(playerCoins)).c_str(), 10, 10, 26, BLACK);
    DrawText(("Wave: " + std::to_string(waveNumber)).c_str(), 10, 50, 26, BLACK);
}

void UIManager::EquipTower(const std::optional<Tower>& tower) {
    if (tower.has_value() && !equippedTower.has_value()) {
        equippedTower = tower;
        HideCursor();
    } else {
        equippedTower = std::nullopt;
        ShowCursor();
    }
}

