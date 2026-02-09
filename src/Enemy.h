#pragma once

#include "raylib.h"

// Enemy struct to hold information
struct Enemy {
	// Update information
	// position of the enemy
	Vector2 position;
	// how fast the enemy moves in pixels
	float speed;
	// remaining hit points of the enemy
	int health;

	// Draw information
	Color color;
	float size;
};