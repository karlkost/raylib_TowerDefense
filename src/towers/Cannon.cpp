#include "towers/Cannon.h"

#include "raymath.h"

Cannon::Cannon(const Texture2D& texture) : m_texture(texture) {
    // TODO: upgrade init/base stat
    m_range = 50.0f;
    m_attackSpeed = 1.0f;
    m_damage = 1;
}

void Cannon::Attack(Enemy& enemy) {
    m_timeSinceLastAttack = 0.0f; // reset timer

    const Vector2 dir = Vector2Subtract(enemy.position, m_position);
    m_rotation = atan2f(dir.y, dir.x) * RAD2DEG - m_rotationOffset;

    // TODO: shoot cannon ball instead which makes the first enemy it hits take damage instead of just "the" enemy
    enemy.health -= m_damage;
}

void Cannon::Draw() const {
    // TODO: fix
    Rectangle src = {0, 0, static_cast<float>(m_texture.width), static_cast<float>(m_texture.height)};
    Rectangle dst = {m_position.x, m_position.y, static_cast<float>(m_texture.width), static_cast<float>(m_texture.height)};
    Vector2 origin = {dst.width / 2, dst.height / 2};

    DrawTexturePro(m_texture, src, dst, origin, m_rotation, WHITE);
}

bool Cannon::EnemyInRange(const Vector2 enemyPosition) const {
    return CheckCollisionPointCircle(enemyPosition, m_position, m_range);
}

std::unique_ptr<Tower> Cannon::clone() const { return std::make_unique<Cannon>(*this); }
