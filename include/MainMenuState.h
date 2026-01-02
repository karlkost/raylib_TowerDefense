#ifndef RAYLIB_TOWERDEFENSE_MENUSTATE_H
#define RAYLIB_TOWERDEFENSE_MENUSTATE_H

#include "GameState.h"
#include "Tower.h"
#include <vector>

class MainMenuState : public GameState {
    std::vector<Tower>& m_towers; //towers in game that the player can select

    std::vector<Tower> m_selectedTowers; //selected towers to be used in game
    Rectangle m_playButton{300, 300, 200, 100};
    Rectangle m_selectTowersButton{300, 500, 200, 100};


public:
    MainMenuState(std::vector<Tower>& loadedTowers) : m_towers(loadedTowers) {};
    void Update(Game& game, float deltaTime) override;
    void Draw() const override;
};

#endif //RAYLIB_TOWERDEFENSE_MENUSTATE_H