#pragma once

#include "raylib.h"

// projectile that the tower shoots
struct Projectile {
	// position of the projectile in the world
	Vector2 position;
	// direction that the projectile will move towards
	Vector2 direction;
	// total distance the projectile has moved (used for cleanup)
	float distanceMoved;
	// speed of the projectile (pixels per second)
	float speed;
	// size of the projectile
	float size;
	// damage the projectile will deal to the enemy
	int damage;
};