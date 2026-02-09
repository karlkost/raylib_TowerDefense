#include "Game.h"

#include "CameraController.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include <vector>
#include <string>
#include <iostream>
#include "raylib.h"

namespace Game {
	CameraController g_playerCameraController{};
	State g_gameState;
	EnemyManager g_enemyManager{ Vector2{0, 0} };
	TowerManager g_towerManager{};

	void Update() {
		if (g_gameState == State::PAUSED) {
			return;
		}
		const float deltaTime = Engine::GetDeltaTime();
		g_playerCameraController.Update(deltaTime, Engine::GetScreenCenteredVector());

		Engine::UpdateMousePosition(g_playerCameraController.getCamera().target);

		g_towerManager.Update(deltaTime, g_enemyManager.GetEnemies());
		g_enemyManager.Update(deltaTime);
	}

	void Draw() {
		BeginDrawing();
		ClearBackground(GRAY);

		BeginMode2D(g_playerCameraController.getCamera());

		// Draw the World & Game Elements
		g_towerManager.Draw();
		g_enemyManager.Draw();
		DrawCircleV(Vector2{ 0, 0 }, 10, PURPLE);
		EndMode2D();

		// temp stuff delete later
		int fps = GetFPS();
		std::string s = "FPS: " + std::to_string(fps);
		DrawText(s.c_str(), 10, 10, 20, BLACK);
		// end of temp stuff


		// Draw UI
		//UI::Draw();
		EndDrawing();
	}

	// TODO: move to enemy or something related once I figure out how I want them to spawn
	//void SpawnEnemy() {
	//	// calculate starting position
	//	int angle = GetRandomValue(0, 359);
	//	float radius = 500.0f;
	//	Vector2 startPos = {
	//		radius * cosf(DEG2RAD * angle),
	//		radius * sinf(DEG2RAD * angle)
	//	};
	//}
}