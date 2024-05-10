#include "Engine.h"
#include "TextRenderer.h"
#include "game/GameEventManager.h"

double Engine::previousTime = 0.0;
double Engine::elapsedTime = 0.0;
double Engine::deltaTime = 0.0;

int Engine::resX = 0;
int Engine::resY = 0;

Engine::Engine(int resX, int resY, bool isFullscreen, bool isVsyncOn) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    createWindow(resX, resY, isFullscreen);

    // Create shaders
    programShader = new Shader("src/shader/vert.glsl", "src/shader/frag.glsl");

    world = new World(programShader->id);

    playerInputManager = new PlayerInputManager(window, &world->player1->position, &world->player2->position, 17);
    pongCollisionManager = new PongCollisionManager(world->ball, 0.03f);
    gameEventManager = new GameEventManager(this, world);
    ballController = new BallController(pongCollisionManager, 
        world->ball, world->player1, world->player2, world->floor, world->ceiling, 0.8f);
    textRenderer = new TextRenderer(programShader->id, "arial.ttf", 96);

    enableVsync(isVsyncOn);
}

Engine::~Engine() {
    delete textRenderer;
    delete ballController;
    delete gameEventManager;
    delete pongCollisionManager;
    delete playerInputManager;
    deleteWorldIfExists();
    delete programShader;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::createWorld() {
    world = new World(programShader->id);

    playerInputManager->setPlayersPositions(&world->player1->position, &world->player2->position);
    pongCollisionManager->setCollidables(world->ball);
    gameEventManager->setWorld(world);
    ballController->setMeshesAndRadii(world->ball, world->player1, world->player2, world->floor, world->ceiling);

    ballController->generateNewRandomBallDirection();
}

void Engine::deleteWorldIfExists() {
    if (world) {
        delete world;
    }
}

void Engine::createWindow(int resX, int resY, bool isFullscreen) {
    this->resX = resX;
    this->resY = resY;

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
    glViewport(0, 0, resX, resY);
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
    //gameEventManager->checkForPlayerWin();

    programShader->use();

    world->render();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textRenderer->renderText("4", glm::vec2(-0.5, 0), glm::vec3(1, 1, 1));
    glDisable(GL_BLEND);
}

void Engine::afterUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}
