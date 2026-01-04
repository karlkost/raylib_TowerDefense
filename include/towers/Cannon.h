#ifndef RAYLIB_TOWERDEFENSE_CANNON_H
#define RAYLIB_TOWERDEFENSE_CANNON_H

#include "Tower.h"

class Cannon : public Tower {
public:
    Cannon(const Texture2D &texture);
    void Attack(Enemy& enemy) override;
    void Draw() const override;
    bool EnemyInRange(Vector2 enemyPosition) const override;
    std::unique_ptr<Tower> clone() const override;

private:
    Texture2D m_texture;
    const float m_rotationOffset = 90.0f;
};

#endif //RAYLIB_TOWERDEFENSE_CANNON_H