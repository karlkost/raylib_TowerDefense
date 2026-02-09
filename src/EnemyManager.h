#pragma once

#include "Enemy.h"
#include <vector>
#include "raylib.h"
#include "raymath.h"

struct EnemyManager {
	EnemyManager(Vector2 target);

	void Update(float dt);
	void Draw() const;
	
	// returns reference to enemies for the towers to loop through
	std::vector<Enemy>& GetEnemies();
	// returns a list of enemies that have reached the target
	std::vector<Enemy> GetEnemiesAtTarget();
private:
	// container for all enemies currently in the world
	std::vector<Enemy> _enemies;
	// container for enemies that have reached the target position
	std::vector<Enemy> _enemiesAtTarget;
	// position that all enemies will move towards
	Vector2 _targetPosition;
};