#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "InputManager.h"
#include "World.h"

class Engine {
	public:
		Engine(int resX, int resY, bool isFullscreen);
		~Engine();
		void enableVsync(bool isEnabled);
		void render();
	private:
		static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
		void createWindow(int resX, int resY, bool isFullscreen);
		bool checkWindowCreatedSuccessfully();
		bool loadGlad();
		void beforeUpdate();
		void update();
		void afterUpdate();

		GLFWwindow* window;
		InputManager* inputManager;
		World* world;
};
