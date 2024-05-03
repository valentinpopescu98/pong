#pragma once
#include <random>

#include "model/Mesh.h"
#include "PongCollisionManager.h"

class BallController {
	public:
		BallController(PongCollisionManager* pongCollisionManager, Mesh* ball, Mesh* player1, Mesh* player2, float speed);
		~BallController();
		void moveBall(float deltaTime);
		void bounceBallIfCollided();
	private:
		void bounceBallOfWall();
		void bounceBallOfPlayer1();
		void bounceBallOfPlayer2();
		
		PongCollisionManager* pongCollisionManager;
		Mesh* ball;
		Mesh* player1;
		Mesh* player2;
		float speed;
		glm::vec3 ballDirection;
};
