#ifndef RAYLIB_FUN_GAME_H
#define RAYLIB_FUN_GAME_H

#include "GameState.h"
#include "MainMenuState.h"
#include <memory>

class Game {
    std::unique_ptr<GameState> currentState;

public:
    void ChangeState(std::unique_ptr<GameState> newState);
    void run();
};

#endif //RAYLIB_FUN_GAME_H