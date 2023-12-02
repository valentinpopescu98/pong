#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window, World* world) {
	this->window = window;
	this->world = world;
}

InputManager::~InputManager() {
	window = NULL;
	world = NULL;
}

void InputManager::treatKeyboardInputs() {
	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
