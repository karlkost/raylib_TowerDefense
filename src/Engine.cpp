#include "Engine.h"

#include "raymath.h"

namespace Engine {
	int g_screenWidth = 800;
	int g_screenHeight = 600;
	float g_deltaTime = 0.0f;
	Vector2 g_cameraMousePosition{ 0, 0 };

	void Init() {
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		InitWindow(g_screenWidth, g_screenHeight, "");
		//SetTargetFPS(120);
	}

	void UpdateGlobals() {
		g_screenWidth = GetScreenWidth();
		g_screenHeight = GetScreenHeight();
		g_deltaTime = GetFrameTime();
		g_cameraMousePosition = Vector2Subtract(GetMousePosition(), GetScreenCenteredVector());
	}

	float GetDeltaTime() {
		return g_deltaTime;
	}

	Vector2 GetScreenCenteredVector() {
		return Vector2{ 
			static_cast<float>(g_screenWidth) / 2.0f, 
			static_cast<float>(g_screenHeight) / 2.0f 
		};
	}

	void UpdateMousePosition(const Vector2 cameraTarget) {
		g_cameraMousePosition = Vector2Add(g_cameraMousePosition, cameraTarget);
	}

	Vector2 GetCameraMousePosition() {
		return g_cameraMousePosition;
	}
}