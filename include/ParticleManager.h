#ifndef RAYLIB_TOWERDEFENSE_PARTICLEMANAGER_H
#define RAYLIB_TOWERDEFENSE_PARTICLEMANAGER_H

#include "Enemy.h"
#include <vector>
#include "raylib.h"

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float speed;
    float remainingLifetime;
    int size;
};

//used for small particles, currently only for when an enemy is hit by an attack
class ParticleManager {
public:
    //singleton setup
    static ParticleManager& GetInstance() {
        static ParticleManager instance;
        return instance;
    }
    ParticleManager(ParticleManager const&) = delete;
    ParticleManager& operator=(ParticleManager const&) = delete;

    void Update(float deltaTime);
    void Draw() const;
    void SpawnEnemyHitParticles(const Enemy& enemy, Vector2 contactPosition);

private:
    ParticleManager() = default;
    std::vector<Particle> m_particles{};
};

#endif //RAYLIB_TOWERDEFENSE_PARTICLEMANAGER_H