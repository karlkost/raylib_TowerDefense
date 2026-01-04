#include "towers/Cannon.h"
#include "raymath.h"

Cannon::Cannon(const Texture2D& texture) : m_texture(texture) {
    //TODO: upgrade init/base stat
    m_range = 50.0f;
    m_attackSpeed = 1.0f;
    m_damage = 1;
}

void Cannon::Attack(Enemy &enemy) {
    const Vector2 dir = Vector2Subtract(enemy.position, m_position);
    m_rotation = atan2f(dir.y, dir.x) * RAD2DEG - m_rotationOffset;

    //TODO: shoot cannon ball instead which makes the first enemy it hits take damage instead of just "the" enemy
    enemy.health -= m_damage;
}

void Cannon::Draw() const {
    //TODO: fix
    const Vector2 centerPos = Vector2(m_position.x - m_texture.height * 0.5f, m_position.y - m_texture.width * 0.5f);

    DrawTextureEx(m_texture, centerPos, m_rotation, 1.0f, WHITE);
}

bool Cannon::EnemyInRange(const Vector2 enemyPosition) const {
    return CheckCollisionPointCircle(enemyPosition, m_position, m_range);
}

std::unique_ptr<Tower> Cannon::clone() const {
    return std::make_unique<Cannon>(*this);
}
