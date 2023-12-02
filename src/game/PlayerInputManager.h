#pragma once
#include "engine/InputManager.h"

class PlayerInputManager : public InputManager {
	public:
		PlayerInputManager(GLFWwindow* window, World* world, float multiplier);
		~PlayerInputManager();
		void treatKeyboardInputs(float deltaTime);
	private:
		Mesh* player1;
		Mesh* player2;
		float multiplier;
};
