#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "InputManager.h"

class Engine {
public:
	Engine();
	~Engine();
	void createWindow(int resX, int resY, bool fullscreen);
	void render();
	void closeProgram(GLFWwindow* window);
private:
	bool checkWindowCreatedSuccessfully();
	bool loadGlad();
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* window;
	InputManager* inputManager;
};
