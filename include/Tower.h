#ifndef RAYLIB_TOWERDEFENSE_TOWER_H
#define RAYLIB_TOWERDEFENSE_TOWER_H

#include <memory>

#include "Enemy.h"

class Tower {
   public:
    Tower() = default;
    virtual ~Tower() = default;

    virtual void Attack(Enemy& enemy) = 0;
    virtual void Draw() const = 0;
    virtual bool EnemyInRange(Vector2 enemyPosition) const = 0;
    virtual std::unique_ptr<Tower> clone() const = 0;

    void UpdateTimeSinceLastAttack(const float deltaTime) { m_timeSinceLastAttack += deltaTime; }
    bool CanAttack() const { return m_timeSinceLastAttack >= (1.0f / m_attackSpeed); }
    void SetPosition(const Vector2 newPosition) { m_position = newPosition; }
    void GetPlacementInformation(Vector2& pos, float& rng) const {
        pos = m_position;
        rng = m_range;
    }

   protected:
    Vector2 m_position = Vector2(0, 0);
    // base tower stats
    float m_range = 0.0f;        // how far the tower can attack (radius of circle)
    float m_attackSpeed = 0.0f;  // how many attacks the tower does per second
    int m_damage = 0;            // how much damage the tower does to an enemy with an attack

    float m_rotation = 0.0f;
    float m_timeSinceLastAttack = 0.0f;
    int m_level = 1;
};

#endif  // RAYLIB_TOWERDEFENSE_TOWER_H