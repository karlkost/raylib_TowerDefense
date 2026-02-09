#include "TowerManager.h"

// REMOVE
#include "Engine.h"
// REMOVE

#include "Utils.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

void TowerManager::Update(float dt, std::vector<Enemy>& enemies) {
	Vector2 mousePosition = Engine::GetCameraMousePosition();
	// temp debug
	if (IsKeyPressed(KEY_C)) {
		std::cout << "spawned tower" << "\n";
		_towers.emplace_back(Tower{
			.position = mousePosition,
			.range = 200.0f,
			.fireRate = 5.0f,
			.damage = 5,
			.timeSinceLastShot = 0.0f
			});
	}

	// tower shooting logic
	for (Tower& tower : _towers) {
		tower.timeSinceLastShot += dt;
		// check if tower can shoot
		if (tower.timeSinceLastShot >= 1.0f / tower.fireRate) {
			// find an enemy in range 
			// currently looks for first since that is how enemies are sorted
			for (Enemy& enemy : enemies) {
				float distance = Vector2Distance(tower.position, enemy.position);
				// shoot the enemy if in range
				if (distance <= tower.range) {
					// spawn a projectile to travel towards the target enemy
					_towerProjectiles.emplace_back(Projectile{
						.position = tower.position,
						.direction = Vector2Normalize(Vector2Subtract(enemy.position, tower.position)),
						.distanceMoved = 0.0f,
						.speed = 1000.0f,
						.size = 5.0f,
						.damage = tower.damage
						});
					tower.timeSinceLastShot = 0.0f;
					break;
				}
			}
		}
	}

	float offScreenDistance = 30.0f;
	// projectile logic
	for (int i = 0; i < _towerProjectiles.size();) {
		Projectile& projectile = _towerProjectiles[i];
		Vector2 movement = Vector2Scale(projectile.direction, projectile.speed * dt);
		Vector2 nextPosition = Vector2Add(projectile.position, movement);
		float distanceMoved = Vector2DistanceSqr(projectile.position, nextPosition);

		// check if projectile is off the screen and remove it through swapping
		projectile.distanceMoved += distanceMoved;
		if (projectile.distanceMoved >= offScreenDistance * offScreenDistance) {
			_towerProjectiles[i] = _towerProjectiles.back();
			_towerProjectiles.pop_back();
			continue;
		}

		// loop through every enemy and see if it collides with projectile's path
		bool enemyHit = false;
		for (Enemy& enemy : enemies) {
			if (CheckCollisionLineCircle(projectile.position, nextPosition, enemy.position, enemy.size + projectile.size)) {
				enemy.health -= projectile.damage;
				enemyHit = true;
				break;
			}
		}

		if (enemyHit) {
			// remove the projectile if it hit an enemy through swapping
			_towerProjectiles[i] = _towerProjectiles.back();
			_towerProjectiles.pop_back();
		} else {
			// move the projectile if no enemy on its path
			projectile.position = nextPosition;
			i++;
		}
	}

	// if left click was pressed check if it was on a tower to display info
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		float towerSize = 10.0f;
		bool clickedTower = false;
		for (int i = 0; i < _towers.size(); i++) {
			const Tower& tower = _towers[i];
			float distance = Vector2DistanceSqr(mousePosition, tower.position);
			if (distance <= towerSize * towerSize) {
				_selectedTowerIndex = i;
				clickedTower = true;
				break;
			}
		}
		// if a tower wasn't clicked stop displaying the range of the last tower
		_selectedTowerIndex = clickedTower ? _selectedTowerIndex : -1;
	}
}

void TowerManager::Draw() const {
	if (_selectedTowerIndex != -1) {
		DrawCircleV(_towers[_selectedTowerIndex].position, _towers[_selectedTowerIndex].range, Fade(GREEN, 0.5f));
	}

	for (const Projectile& projectile : _towerProjectiles) {
		DrawCircleV(projectile.position, projectile.size, BLACK);
	}

	for (const Tower& tower : _towers) {
		DrawCircleV(tower.position, 10.0f, BLUE);
	}

	
}