#include "ParticleManager.h"

#include "DrawCenteredRectangle.h"
#include "raymath.h"

void ParticleManager::Update(const float deltaTime) {
    for (Particle& p : m_particles) {
        p.remainingLifetime -= deltaTime;
        p.position = Vector2Add(p.position, Vector2Scale(p.velocity, deltaTime));
    }

    std::erase_if(m_particles, [](const Particle& p) { return p.remainingLifetime <= 0.0f; });
}

void ParticleManager::Draw() const {
    for (const Particle& p : m_particles) {
        DrawCenteredRectangle(p);
    }
}

static constexpr float PARTICLE_LIFETIME = 0.35f;
static constexpr int NUM_PARTICLES = 3;

void ParticleManager::SpawnEnemyHitParticles(const Enemy& enemy, const Vector2 contactPosition) {
    // calculate angle of hit relative to x-axis
    const Vector2 dir = Vector2Subtract(enemy.position, contactPosition);
    float contactAngle = atan2f(dir.y, dir.x) * RAD2DEG - 180;

    if (contactAngle < 0) contactAngle += 360.0f;

    // spawn particles based on the angle
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        Particle p{};
        p.position = contactPosition;
        p.speed = 75.0f;
        p.color = enemy.color;

        // spread so particles go different directions
        const auto spread = static_cast<float>(GetRandomValue(-30, 30));
        const float particleAngle = contactAngle + spread;

        const float particleRadians = particleAngle * DEG2RAD;
        p.velocity = {cosf(particleRadians) * p.speed, sinf(particleRadians) * p.speed};
        p.remainingLifetime = PARTICLE_LIFETIME;
        p.size = enemy.size / 2;

        m_particles.push_back(p);
    }
}
