#pragma once
#include <glm/gtc/type_ptr.hpp>

#include "engine/InputManager.h"

class PlayerInputManager : public InputManager {
	public:
		PlayerInputManager(GLFWwindow* window, glm::vec3* player1Pos, glm::vec3* player2Pos, float multiplier);
		~PlayerInputManager();
		void treatKeyboardInputs(float deltaTime);
		void setPlayersPositions(glm::vec3* player1Pos, glm::vec3* player2Pos);
	private:
		glm::vec3* player1Pos;
		glm::vec3* player2Pos;
		float multiplier;
};
