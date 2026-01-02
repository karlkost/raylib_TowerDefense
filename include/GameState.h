#ifndef RAYLIB_TOWERDEFENSE_GAMESTATE_H
#define RAYLIB_TOWERDEFENSE_GAMESTATE_H

class Game;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void Update(Game& game, float deltaTime) = 0;
    virtual void Draw() const = 0;
};

#endif //RAYLIB_TOWERDEFENSE_GAMESTATE_H