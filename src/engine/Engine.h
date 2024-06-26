#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "game/PlayerInputManager.h"
#include "game/PongCollisionManager.h"
#include "game/BallController.h"
#include "World.h"

class GameEventManager;

class Engine {
	public:
		Engine(int resX, int resY, bool isFullscreen, bool isVsyncOn);
		~Engine();
		void createWorld();
		void deleteWorldIfExists();
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
		World* world;
		PlayerInputManager* playerInputManager;
		PongCollisionManager* pongCollisionManager;
		GameEventManager* gameEventManager;
		BallController* ballController;
};
