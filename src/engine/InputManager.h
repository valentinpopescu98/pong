#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputManager {
	public:
		InputManager(GLFWwindow* window);
		~InputManager();
		void treatKeyboardInputs();
	protected:
		GLFWwindow* window;
};
