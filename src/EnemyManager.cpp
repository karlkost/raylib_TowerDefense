#include "EnemyManager.h"

// REMOVE
#include "Engine.h"
// REMOVE

#include <iostream>

EnemyManager::EnemyManager(Vector2 targetPosition = Vector2Zero()) 
	: _targetPosition(targetPosition) 
{
}

void EnemyManager::Update(const float deltaTime) {
	// temp debug
	if (IsKeyPressed(KEY_Z)) {
		std::cout << "spawned" << std::endl;
		_enemies.emplace_back(Enemy{
			.position = Engine::GetCameraMousePosition(),
			.speed = 25,
			.health = 1,
			.color = RED,
			.size = 5.0f
			});
	}
	// temp debug
	if (IsKeyPressed(KEY_X)) {
		std::cout << "spawned 2" << std::endl;
		_enemies.emplace_back(Enemy{
			.position = Engine::GetCameraMousePosition(),
			.speed = 50,
			.health = 1,
			.color = RED,
			.size = 5.0f
			});
	}


	for (Enemy& enemy : _enemies) {
		// skip dead enemies
		if (enemy.health <= 0) continue;

		// move towards target position
		enemy.position = Vector2MoveTowards(enemy.position, _targetPosition, enemy.speed * deltaTime);
	}

	// sort based on how close to the target
	for (size_t i = 1; i < _enemies.size(); ++i) {
		Enemy enemy = _enemies[i];
		float distanceFromTarget = Vector2DistanceSqr(enemy.position, _targetPosition);
		
		size_t j = i;
		while (j > 0 && Vector2DistanceSqr(_enemies[j - 1].position, _targetPosition) > distanceFromTarget) {
			_enemies[j] = _enemies[j - 1];
			--j;
		}

		_enemies[j] = enemy;
	}

	// Check if enemies reached the target
	for (int i = 0; i < _enemies.size(); ++i) {
		Enemy& enemy = _enemies[i];
		if (Vector2Equals(enemy.position, _targetPosition)) {
			// Add a copy of the enemy in the target container
			_enemiesAtTarget.push_back(enemy);
			enemy.health = 0;
		} else {
			// since they are sorted we can break at the first enemy not at the target
			break;
		}
	}

	// Remove all dead enemies (and enemies at target)
	_enemies.erase(
		std::remove_if(_enemies.begin(), _enemies.end(),
			[](const Enemy& e) {
				return e.health <= 0;
			}),
		_enemies.end()
	);
}

void EnemyManager::Draw() const {
	for (const Enemy& enemy : _enemies) {
		DrawCircleV(enemy.position, enemy.size, enemy.color);
	}
}

std::vector<Enemy>& EnemyManager::GetEnemies() {
	return _enemies;
}

std::vector<Enemy> EnemyManager::GetEnemiesAtTarget() {
	return std::move(_enemiesAtTarget);
}
