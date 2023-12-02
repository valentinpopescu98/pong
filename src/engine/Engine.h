#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "World.h"

class InputManager;

class Engine {
	public:
		Engine(int resX, int resY, bool isFullscreen, bool isVsyncOn);
		~Engine();
		static void setTimeValues();
		static void enableVsync(bool isEnabled);
		void render();

		static double previousTime;
		static double elapsedTime;
		static double deltaTime;
	private:
		static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
		void createWindow(int resX, int resY, bool isFullscreen);
		bool checkWindowCreatedSuccessfully();
		static bool loadGlad();
		void beforeUpdate();
		void update();
		void afterUpdate();

		GLFWwindow* window;
		InputManager* inputManager;
		World* world;
};