#pragma once

#include "raylib.h"

// Used for information pertaining to the window and frames
namespace Engine {
	// Initialize the game window and textures
	void Init();
	// Update the globals (delta time & screen size, and mouse position based on screen size)
	void UpdateGlobals();
	// Return time between frames
	float GetDeltaTime();
	// Return a centered vector based on screen size
	Vector2 GetScreenCenteredVector();
	// Update the mouse position based on camera movement
	void UpdateMousePosition(const Vector2 cameraTarget);
	// Return mouse position in the world based on camera movement and screen size
	Vector2 GetCameraMousePosition();
}