#pragma once
#include "engine/InputManager.h"
#include "model/Mesh.h"

class PlayerInputManager : public InputManager {
	public:
		PlayerInputManager(GLFWwindow* window, Mesh* player1, Mesh* player2, float multiplier);
		~PlayerInputManager();
		void treatKeyboardInputs(float deltaTime);
		void setPlayers(Mesh* player1, Mesh* player2);
	private:
		Mesh* player1;
		Mesh* player2;
		float multiplier;
};
