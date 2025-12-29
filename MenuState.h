#ifndef RAYLIB_TOWERDEFENSE_MENUSTATE_H
#define RAYLIB_TOWERDEFENSE_MENUSTATE_H

#include "GameState.h"
#include "Tower.h"
#include <vector>

class MenuState : public GameState {
    std::vector<Tower> selectedTowers;
    Rectangle playButton{300, 300, 200, 100};

public:
    void Update(Game& game, float deltaTime) override;
    void Draw() const override;
};

#endif //RAYLIB_TOWERDEFENSE_MENUSTATE_H