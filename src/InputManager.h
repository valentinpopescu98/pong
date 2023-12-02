#pragma once
#include <GLFW/glfw3.h>

class InputManager {
	public:
		InputManager(GLFWwindow* window);
		~InputManager();
		void treatKeyboardInputs();
	private:
		GLFWwindow* window;
};
