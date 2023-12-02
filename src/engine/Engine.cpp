#include "Engine.h"
#include "InputManager.h"

double Engine::previousTime = 0;
double Engine::elapsedTime = 0;
double Engine::deltaTime = 0;

Engine::Engine(int resX, int resY, bool isFullscreen, bool isVsyncOn) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    createWindow(resX, resY, isFullscreen);
    world = new World();
    inputManager = new InputManager(window, world);

    enableVsync(isVsyncOn);

    /*previousTime = 0.0;
    elapsedTime = 0.0;
    deltaTime = 0.0;*/
}

Engine::~Engine() {
    delete inputManager;
    delete world;
    glfwDestroyWindow(window);

    glfwTerminate();
}

void Engine::createWindow(int resX, int resY, bool isFullscreen) {
    GLFWmonitor* primaryMonitor = isFullscreen ? glfwGetPrimaryMonitor() : NULL;
    window = glfwCreateWindow(resX, resY, "Pong", primaryMonitor, NULL);

    if (!checkWindowCreatedSuccessfully()) {
        return;
    }
    glfwMakeContextCurrent(window);

    if (!loadGlad()) {
        return;
    }

    // Set initial viewport size
    glViewport(0, 0, resX, resY);

    // Change viewport on window resize
    glfwSetFramebufferSizeCallback(window, Engine::frameBufferSizeCallback);
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

void Engine::setTimeValues() {
    elapsedTime = glfwGetTime();
    deltaTime = elapsedTime - previousTime;
    previousTime = elapsedTime;
}

void Engine::enableVsync(bool isEnabled) {
    glfwSwapInterval(isEnabled);
}

void Engine::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Engine::render() {
    while (!glfwWindowShouldClose(window)) {
        beforeUpdate();
        update();
        afterUpdate();

        // Compute time since last frame
        setTimeValues();
    }
}

void Engine::beforeUpdate() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::update() {
    inputManager->treatKeyboardInputs();

    world->render();
}

void Engine::afterUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}
