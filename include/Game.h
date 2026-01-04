#ifndef RAYLIB_TOWERDEFENSE_GAME_H
#define RAYLIB_TOWERDEFENSE_GAME_H

#include <memory>

#include "GameState.h"

class Game {
   public:
    void ChangeState(std::unique_ptr<GameState> newState);
    void run();

   private:
    std::unique_ptr<GameState> m_currentState;
};

#endif  // RAYLIB_TOWERDEFENSE_GAME_H