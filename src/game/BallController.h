#pragma once
#include <random>

#include "model/obj/MeshObj.h"
#include "PongCollisionManager.h"

class BallController {
	public:
		BallController(PongCollisionManager* pongCollisionManager,
			MeshObj* ball, MeshObj* player1, MeshObj* player2, MeshObj* floor, MeshObj* ceiling, float ballSpeed);
		~BallController();
		void moveBall(float deltaTime);
		void bounceBallIfCollided();
		void generateNewRandomBallDirection();
		void setMeshesAndRadii(MeshObj* ball, MeshObj* player1, MeshObj* player2, MeshObj* floor, MeshObj* ceiling);
	private:
		void bounceBallOfWall();
		void bounceBallOfPlayer1();
		void bounceBallOfPlayer2();
		
		PongCollisionManager* pongCollisionManager;
		MeshObj *ball;
		MeshObj *player1, *player2;
		MeshObj *floor, *ceiling;
		glm::vec3 ballDirection;
		float ballSpeed;

		glm::vec3 ballRadius;
		float player1Radius;
		float player2Radius;
		float wallRadius;
};
