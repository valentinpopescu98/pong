#pragma once
#include "World.h"
#include "Engine.h"

class InputManager {
	public:
		InputManager(GLFWwindow* window, World* world);
		~InputManager();
		void treatKeyboardInputs();
	private:
		GLFWwindow* window;
		World* world;
};
