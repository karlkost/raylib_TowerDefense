#include "MenuState.h"
#include "Game.h"
#include "PlayingState.h"

void MenuState::Update(Game& game, const float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), playButton)) {
            game.ChangeState(std::make_unique<PlayingState>());
        }
    }
}

void MenuState::Draw() const {
    DrawText("TOWER DEFENSE GAME", 300, 200, 30, BLACK);
    DrawRectangleRec(playButton, BLACK);
    DrawText("PLAY", 350, 350, 30, WHITE);
}