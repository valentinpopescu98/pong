#include "PlayerInputManager.h"

PlayerInputManager::PlayerInputManager(GLFWwindow* window, glm::vec3* player1Pos, glm::vec3* player2Pos, float multiplier)
	: InputManager(window) {
	setPlayersPositions(player1Pos, player2Pos);
	this->multiplier = multiplier;
}

PlayerInputManager::~PlayerInputManager() {
	player1Pos = NULL;
	player2Pos = NULL;
	multiplier = 1.0f;
}

void PlayerInputManager::treatKeyboardInputs(float deltaTime) {
	InputManager::treatKeyboardInputs();

	// Move player1
	if (player1Pos->y < 0.75 && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		*player1Pos += multiplier * glm::vec3(0, 0.1, 0) * deltaTime;
	}
	else if (player1Pos->y > -0.75 && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		*player1Pos += multiplier * glm::vec3(0, -0.1, 0) * deltaTime;
	}

	// Move player2
	if (player2Pos->y < 0.75 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		*player2Pos += multiplier * glm::vec3(0, 0.1, 0) * deltaTime;
	}
	else if (player2Pos->y > -0.75 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		*player2Pos += multiplier * glm::vec3(0, -0.1, 0) * deltaTime;
	}
}

void PlayerInputManager::setPlayersPositions(glm::vec3* player1Pos, glm::vec3* player2Pos) {
	this->player1Pos = player1Pos;
	this->player2Pos = player2Pos;
}
