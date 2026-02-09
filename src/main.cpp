#include "raylib.h"
#include "Engine.h"
#include "Game.h"

int main() {
	Engine::Init();

	while (!WindowShouldClose()) {
		Engine::UpdateGlobals();
		
		Game::Update();
		Game::Draw();
	}
}
