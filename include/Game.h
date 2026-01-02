#ifndef RAYLIB_TOWERDEFENSE_GAME_H
#define RAYLIB_TOWERDEFENSE_GAME_H

#include "GameState.h"
#include <memory>

class Game {
    std::unique_ptr<GameState> currentState;

public:
    void ChangeState(std::unique_ptr<GameState> newState);
    void run();
};

#endif //RAYLIB_TOWERDEFENSE_GAME_H