#pragma once

#include "raylib.h"

// Tower struct for holding information
struct Tower {
	// position of the tower on the map
	Vector2 position;
	// radius of a circle orginating from the position
	float range;
	// shots per second
	float fireRate;
	// damage of the projectile
	int damage;
	// timer to keep track when the last shot was
	float timeSinceLastShot;
};