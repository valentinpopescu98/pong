#include "PlayerInputManager.h"

PlayerInputManager::PlayerInputManager(GLFWwindow* window, World* world, float multiplier) 
	: InputManager(window, world) {
	this->player1 = world->player1;
	this->player2 = world->player2;
	this->multiplier = multiplier;
}

PlayerInputManager::~PlayerInputManager() {
	player1 = NULL;
	player2 = NULL;
	multiplier = 1.0f;
}

void PlayerInputManager::treatKeyboardInputs(float deltaTime) {
	InputManager::treatKeyboardInputs();

	// Move player1
	if (player1->position.y < 0.8 && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		player1->position += multiplier * glm::vec3(0, 0.1, 0) * deltaTime;
	}
	else if (player1->position.y > -0.8 && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		player1->position += multiplier * glm::vec3(0, -0.1, 0) * deltaTime;
	}

	// Move player2
	if (player2->position.y < 0.8 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		player2->position += multiplier * glm::vec3(0, 0.1, 0) * deltaTime;
	}
	else if (player2->position.y > -0.8 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		player2->position += multiplier * glm::vec3(0, -0.1, 0) * deltaTime;
	}
}
