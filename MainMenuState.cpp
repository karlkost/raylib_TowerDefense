#include "MainMenuState.h"
#include "Game.h"
#include "PlayingState.h"

void MainMenuState::Update(Game& game, const float deltaTime) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && menuState == MenuState::MAIN) {
        if (CheckCollisionPointRec(GetMousePosition(), playButton)) {
            game.ChangeState(std::make_unique<PlayingState>(towers));
        } else if (CheckCollisionPointRec(GetMousePosition(), selectTowersButton)) {
            menuState = MenuState::TOWER_SELECT;
        }
    }


}

void MainMenuState::Draw() const {
    if (menuState == MenuState::MAIN) {
        DrawText("TOWER DEFENSE GAME", 300, 200, 30, BLACK);
        DrawRectangleRec(playButton, BLACK);
        DrawText("PLAY", 350, 350, 30, WHITE);
        DrawRectangleRec(selectTowersButton, BLACK);
        DrawText("SELECT TOWERS", 350, 550, 12, WHITE);
    } else if (menuState == MenuState::TOWER_SELECT) {

    } else {

    }
}