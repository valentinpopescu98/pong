#pragma once
#include <random>

#include "model/Mesh.h"
#include "engine/CollisionManager.h"

class BallController {
	public:
		BallController(CollisionManager* collisionManager, Mesh* ball, Mesh* player1, Mesh* player2, float speed);
		~BallController();
		void moveBall(float deltaTime);
		void bounceBallIfCollided();
	private:
		void bounceBallOfWall();
		void bounceBallOfPlayer1();
		void bounceBallOfPlayer2();
		
		CollisionManager* collisionManager;
		Mesh* ball;
		Mesh* player1;
		Mesh* player2;
		float speed;
		glm::vec3 ballDirection;
};
