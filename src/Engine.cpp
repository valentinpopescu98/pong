#include "Engine.h"

Engine::Engine() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    inputManager = new InputManager();
}

Engine::~Engine() {
    //glfwDestroyWindow(this->window);
    delete inputManager;

    glfwTerminate();
}

void Engine::createWindow(int resX, int resY, bool fullscreen) {
    GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
    this->window = glfwCreateWindow(resX, resY, "Pong", primaryMonitor, NULL);

    if (!checkWindowCreatedSuccessfully()) return;
    glfwMakeContextCurrent(window);

    if (!loadGlad()) return;

    // Set initial viewport size
    glViewport(0, 0, resX, resY);

    // Change viewport on window resize
    glfwSetFramebufferSizeCallback(window, Engine::frameBufferSizeCallback);
}

void Engine::render() {
    while (!glfwWindowShouldClose(this->window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        inputManager->closeWindow(this->window);

        glfwPollEvents();
        glfwSwapBuffers(this->window);
    }
}

bool Engine::checkWindowCreatedSuccessfully() {
    if (this->window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    return true;
}

bool Engine::loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Engine::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
