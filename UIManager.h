#ifndef RAYLIB_TOWERDEFENSE_UIMANAGER_H
#define RAYLIB_TOWERDEFENSE_UIMANAGER_H


#include "TowerManager.h"
#include <optional>


class UIManager {
    //initialized variables
    //std::vector<Tower> towers; //towers which the player has available (at the bottom of the screen)
    int playerCoins; //TODO: change to references once main menu is added
    int playerLifeCount;
    int waveNumber;

    //defaults
    std::optional<Tower> equippedTower; //tower which the player has equipped (for placing)

public:
    UIManager();
    void Update();
    void Draw() const;
    void EquipTower(const std::optional<Tower>& tower);
};

//display coins & lives
//display tower ui (bottom of the screen so player can see available towers) & tower placement
//display wave # (add a cool animation for wave change!)


#endif //RAYLIB_TOWERDEFENSE_UIMANAGER_H