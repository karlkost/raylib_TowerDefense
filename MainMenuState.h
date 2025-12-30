#ifndef RAYLIB_TOWERDEFENSE_MENUSTATE_H
#define RAYLIB_TOWERDEFENSE_MENUSTATE_H

#include "GameState.h"
#include "Tower.h"
#include <vector>

enum class MenuState {
    MAIN,
    TOWER_SELECT
};

class MainMenuState : public GameState {
    std::vector<Tower>& towers; //towers in game that the player can select

    std::vector<Tower> selectedTowers; //selected towers to be used in game
    Rectangle playButton{300, 300, 200, 100};
    Rectangle selectTowersButton{300, 500, 200, 100};
    MenuState menuState = MenuState::MAIN;

public:
    MainMenuState(std::vector<Tower>& loadedTowers) : towers(loadedTowers) {};
    void Update(Game& game, float deltaTime) override;
    void Draw() const override;
};

#endif //RAYLIB_TOWERDEFENSE_MENUSTATE_H