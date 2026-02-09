#pragma once

#include "Tower.h"
#include "Enemy.h"
#include "Projectile.h"
#include <vector>

struct TowerManager {
	// tower shooting and projecitles
	void Update(float dt, std::vector<Enemy>& enemies);
	// draw tower stuff and projectiles
	void Draw() const;
private:
	// container for the towers placed
	std::vector<Tower> _towers;
	// container for the projectiles that towers shoot
	std::vector<Projectile> _towerProjectiles;
	// index for the clicked tower to see it's range/stats
	int _selectedTowerIndex = -1;

};