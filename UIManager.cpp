#include "UIManager.h"
#include <string>

UIManager::UIManager() :
playerCoins(0), playerLifeCount(0), waveNumber(0),
state(NONE), dragArea(), mousePosition(Vector2Zero()), startDragPosition(Vector2Zero())
{

}

void UIManager::Update() {
    if (IsKeyPressed('1')) {
        if (state == PLACING_TOWER) {
            state = NONE;
            equippedTower = std::nullopt;
            ShowCursor();
        } else {
            state = PLACING_TOWER;
            HideCursor();
        }
    }

    if (equippedTower.has_value() && state == PLACING_TOWER) equippedTower.value().position = GetMousePosition();

    //start of rectangle drag for multi select
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && state == NONE) {
        startDragPosition = GetMousePosition();
        state = DRAG_SELECT;
    }

    //end of rectangle drag for multi select
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && state == DRAG_SELECT) {
        const Vector2 endMousePosition = GetMousePosition();

        const float x = std::min(startDragPosition.x, endMousePosition.x);
        const float y = std::min(startDragPosition.y, endMousePosition.y);
        const float width = std::abs(endMousePosition.x - startDragPosition.x);
        const float height = std::abs(endMousePosition.y - startDragPosition.y);

        dragArea = {x, y, width, height};
        state = NONE;
    }
}

void UIManager::Draw() const {
    //draw UI
    if (equippedTower.has_value() && state == PLACING_TOWER) TowerManager::DisplayPlacement(equippedTower.value(), true);

    //draw text
    DrawText(("Coins: " + std::to_string(playerCoins)).c_str(), 10, 10, 26, BLACK);
    DrawText(("Wave: " + std::to_string(waveNumber)).c_str(), 10, 50, 26, BLACK);
}

UIState UIManager::GetState() const {
    return state;
}

Rectangle UIManager::GetDragArea() const {
    return dragArea;
}