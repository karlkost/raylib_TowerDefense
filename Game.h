#ifndef RAYLIB_FUN_GAME_H
#define RAYLIB_FUN_GAME_H

#include "GameState.h"
#include "MenuState.h"
#include <memory>

class Game {
    std::unique_ptr<GameState> currentState = std::make_unique<MenuState>();

public:
    void ChangeState(std::unique_ptr<GameState> newState);
    void run();
};

#endif //RAYLIB_FUN_GAME_H