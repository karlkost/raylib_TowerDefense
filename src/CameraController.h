#pragma once

#include "Engine.h"
#include "raylib.h"
#include "raymath.h"

// 2D Camera for movement
struct CameraController {
	CameraController(
		const Vector2 offset = Engine::GetScreenCenteredVector(), 
		const Vector2 target = Vector2{0, 0},
		const float rotation = 0.0f, 
		const float zoom = 1.0f) 
	{
		_camera = { offset, target, rotation, zoom };
	}
	void Update(const float dt, const Vector2 cameraOffset) {

		// Keep camera centered based on screen size
		_camera.offset = cameraOffset;

		// Move camera with WASD
		Vector2 cameraMovement = { 0.0f, 0.0f };
		
		if (IsKeyDown(KEY_W)) cameraMovement.y -= 1;
		if (IsKeyDown(KEY_S)) cameraMovement.y += 1;
		if (IsKeyDown(KEY_A)) cameraMovement.x -= 1;
		if (IsKeyDown(KEY_D)) cameraMovement.x += 1;
		
		cameraMovement = Vector2Normalize(cameraMovement);
		cameraMovement = Vector2Scale(cameraMovement, _cameraMoveSpeed * dt);
		_camera.target = Vector2Add(_camera.target, cameraMovement);
	}
	const Camera2D& getCamera() const { return _camera; }
private:
	float _cameraMoveSpeed = 300.0f;
	Camera2D _camera;
};