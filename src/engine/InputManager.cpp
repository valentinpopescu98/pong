#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window) {
	this->window = window;
}

InputManager::~InputManager() {
	window = NULL;
}

void InputManager::treatKeyboardInputs() {
	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
