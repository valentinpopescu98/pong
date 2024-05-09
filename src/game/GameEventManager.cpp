#include "GameEventManager.h"
#include "engine/Engine.h"

GameEventManager::GameEventManager(Engine* engine, World* world) {
	this->engine = engine;
	setWorld(world);

	player1Score = 0;
	player2Score = 0;
}

GameEventManager::~GameEventManager() {
	engine = NULL;
	world = NULL;

	player1Score = 0;
	player1Score = 0;
}

void GameEventManager::checkForPlayerWin() {
	if (world->ball->position.x < world->player1->position.x) {
		player2Score++;
		resetGame();
	} else if (world->ball->position.x > world->player2->position.x) {
		player1Score++;
		resetGame();
	}
}

void GameEventManager::resetGame() {
	engine->deleteWorldIfExists();
	engine->createWorld();
}

void GameEventManager::setWorld(World* world) {
	this->world = world;
}
