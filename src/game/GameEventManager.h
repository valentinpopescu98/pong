#pragma once
#include "engine/World.h"

class Engine;

class GameEventManager {
	public:
		GameEventManager(Engine* engine, World* world);
		~GameEventManager();
		void checkForPlayerWin();
		void setWorld(World* world);
	private:
		void resetGame();
		Engine* engine;
		World* world;

		int player1Score;
		int player2Score;
};
