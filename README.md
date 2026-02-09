# Raylib Tower Defense

## Project Description
This project was created to learn and practice using C++ 20 by creating a game using the [Raylib](https://www.raylib.com/) graphics library.
The goal of this game is to prevent the enemies reaching the core by placing towers which will shoot at them.

## Build Instructions
### Requirements
* CMake 3.11+
* Visual Studio with MSVC (VS 2019+)

### Process
1. Clone the repository - https://github.com/karlkost/raylib_TowerDefense
2. Then use these terminal commands to build
```bash
cd raylib_TowerDefense
mkdir build
cd build
cmake ..
cmake --build .
```
3. After it's done building run the game by entering these commands (assuming you are building with Debug)
```bash
cd Debug
.\raylib_TowerDefense.exe
```

## Controls & Info
- Press **C** to spawn a tower at the current mouse position in the game
	- The towers will attempt to shoot at the closest enemy within their range (range can be seen by left clicking on a tower)
- Press **X** to spawn a fast enemy at mouse position and **Z** to spawn a slow enemy
	- Enemies will take damage once they get hit by a tower's bullet (they will die instantly for now as they all have one health)

## Future Additions
- Spawn "portals" where the enemy will spawn from and move towards the core
- Visual confirmation that enemy takes damage (health bar or particles)
- Player Base Health
- Currency to gain & use
- User Interface
  - Wave Number & Coins
  - Available Towers (a bar at the bottom of the screen showing the towers you can place and prices)
  - Tower Screen (for selected tower to see upgrades, targeting, and stats)
