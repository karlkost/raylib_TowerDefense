#pragma once

// Manages the game state and logic
namespace Game {
	enum class State {
		PLAYING,
		PAUSED,
		GAME_OVER
	};

	void Init();
	void Update();
	void Draw();
}