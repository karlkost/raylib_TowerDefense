#include "MainMenuState.h"
#include "Game.h"
#include "PlayingState.h"
#include "DebugMap.h"

void MainMenuState::Update(Game& game, const float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), playButton)) {
            game.ChangeState(std::make_unique<PlayingState>(towers, DebugMap::GetWaypoints()));
        }
    }
}

void MainMenuState::Draw() const {
    DrawText("TOWER DEFENSE GAME", 300, 200, 30, BLACK);
    DrawRectangleRec(playButton, BLACK);
    DrawText("PLAY", 350, 350, 30, WHITE);
}