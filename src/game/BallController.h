#pragma once
#include <random>

#include "model/Mesh.h"

class BallController {
	public:
		BallController(Mesh* ball, float speed);
		~BallController();
		void moveBall(float deltaTime);
	private:
		Mesh* ball;
		float speed;
		glm::vec3 lastAngle;
};
