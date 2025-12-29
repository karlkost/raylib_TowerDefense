#ifndef RAYLIB_TOWERDEFENSE_UIMANAGER_H
#define RAYLIB_TOWERDEFENSE_UIMANAGER_H


#include "TowerManager.h"
#include <optional>

enum class UIState {
    NONE,
    PLACING_TOWER,
    DRAG_SELECT,
};

class UIManager {
    //initialized variables
    std::optional<Tower> towers; //towers which the player has available TODO: remove optional when main menu is added and change to vector
    int playerCoins; //TODO: change to references once main menu is added
    int playerLifeCount;
    int waveNumber;

    //defaults
    std::optional<Tower> equippedTower; //tower which the player has equipped (for placing)
    UIState state;

    Rectangle dragArea;
    Vector2 mousePosition;
    Vector2 startDragPosition;

public:
    UIManager();
    void Update();
    void Draw() const;
    UIState GetState() const;
    Rectangle GetDragArea() const;
    void EquipTower(Tower& tower);
};

//display coins & lives
//display tower ui (bottom of the screen so player can see available towers) & tower placement
//display wave # (add a cool animation for wave change!)
//

#endif //RAYLIB_TOWERDEFENSE_UIMANAGER_H