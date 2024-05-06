#pragma once
#include <random>

#include "model/Mesh.h"
#include "PongCollisionManager.h"

class BallController {
	public:
		BallController(PongCollisionManager* pongCollisionManager,
			Mesh* ball, Mesh* player1, Mesh* player2, Mesh* floor, Mesh* ceiling, float ballSpeed);
		~BallController();
		void moveBall(float deltaTime);
		void bounceBallIfCollided();
		void generateNewRandomBallDirection();
		void setMeshesAndRadii(Mesh* ball, Mesh* player1, Mesh* player2, Mesh* floor, Mesh* ceiling);
	private:
		void bounceBallOfWall();
		void bounceBallOfPlayer1();
		void bounceBallOfPlayer2();
		
		PongCollisionManager* pongCollisionManager;
		Mesh* ball;
		Mesh* player1;
		Mesh* player2;
		Mesh* floor;
		Mesh* ceiling;
		glm::vec3 ballDirection;
		float ballSpeed;

		glm::vec3 ballRadius;
		float player1Radius;
		float player2Radius;
		float wallRadius;
};
