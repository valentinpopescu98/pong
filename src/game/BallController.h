#pragma once
#include <random>

#include "model/Mesh.h"
#include "engine/CollisionManager.h"

class BallController {
	public:
		BallController(CollisionManager* collisionManager, Mesh* ball, float speed);
		~BallController();
		void moveBall(float deltaTime);
		void repelBallIfCollided();
	private:
		void repelBall();
		
		CollisionManager* collisionManager;
		Mesh* ball;
		float speed;
		glm::vec3 lastAngle;
};
