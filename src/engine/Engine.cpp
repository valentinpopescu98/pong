#include "Engine.h"
#include "game/GameEventManager.h"

double Engine::previousTime = 0.0;
double Engine::elapsedTime = 0.0;
double Engine::deltaTime = 0.0;

Engine::Engine(int resX, int resY, bool isFullscreen, bool isVsyncOn) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    createWindow(resX, resY, isFullscreen);
    world = new World();
    playerInputManager = new PlayerInputManager(window, world->player1, world->player2, 10);
    pongCollisionManager = new PongCollisionManager(world->floor, world->ceiling, world->player1, world->player2, world->ball, 0.03);
    gameEventManager = new GameEventManager(this, world);
    ballController = new BallController(pongCollisionManager, world->ball, world->player1, world->player2, 0.5);

    enableVsync(isVsyncOn);
}

Engine::~Engine() {
    delete ballController;
    delete gameEventManager;
    delete pongCollisionManager;
    delete playerInputManager;
    deleteWorldIfExists();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::createWorld() {
    world = new World();

    playerInputManager->setPlayers(world->player1, world->player2);
    pongCollisionManager->setCollidables(world->floor, world->ceiling, world->player1, world->player2, world->ball);
    gameEventManager->setWorld(world);
    ballController->setBallAndPlayers(world->ball, world->player1, world->player2);

    ballController->generateNewRandomBallDirection();
}

void Engine::deleteWorldIfExists() {
    if (world) {
        delete world;
    }
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
    ballController->moveBall((float) deltaTime);
    ballController->bounceBallIfCollided();
    playerInputManager->treatKeyboardInputs((float) deltaTime);
    gameEventManager->checkForPlayerWin();

    world->render();
}

void Engine::afterUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}
