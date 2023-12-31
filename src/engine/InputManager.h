#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "World.h"

class InputManager {
	public:
		InputManager(GLFWwindow* window, World* world);
		~InputManager();
		void treatKeyboardInputs();
	protected:
		GLFWwindow* window;
		World* world;
};
