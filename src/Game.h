#pragma once

// Manages the game state and logic
namespace Game {
	enum class State {
		PLAYING,
		PAUSED,
		GAME_OVER
	};
	// load textures for the towers (not implemented yet)
	//void Init();
	// main game logic such as enemy, towers, camera
	void Update();
	// draw all the main game stuff
	void Draw();
}