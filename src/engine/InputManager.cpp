#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window, World* world) {
	this->window = window;
	this->world = world;
}

InputManager::~InputManager() {
	window = NULL;
	world = NULL;
}

void InputManager::treatKeyboardInputs(float deltaTime) {
	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// Move player1
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		world->player1->position += glm::vec3(0, 0.1, 0) * deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		world->player1->position += glm::vec3(0, -0.1, 0) * deltaTime;
	}

	// Move player2
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		world->player2->position += glm::vec3(0, 0.1, 0) * deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		world->player2->position += glm::vec3(0, -0.1, 0) * deltaTime;
	}
}
