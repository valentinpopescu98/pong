#include "BallController.h"
#include <iostream>

BallController::BallController(CollisionManager* collisionManager, Mesh* ball, float speed) {
	this->collisionManager = collisionManager;
	this->ball = ball;
	this->speed = speed;

	// Use a random_device to seed the random number generator
	std::random_device rd;

	// Use the Mersenne Twister engine for generating random numbers
	std::mt19937 gen(rd());

	// Define the distribution for floats between -1 and 1 (inclusive)
	std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

	// Generate the direction for the OX axis
	float angleX = distribution(gen) > 0 ? 1 : -1;

	// Generate the direction for the OY axis
	float angleY = distribution(gen);

	lastAngle = glm::vec3(angleX, angleY, 0);
	//lastAngle = glm::vec3(0, 1, 0);
}

BallController::~BallController() {
	ball = NULL;
	collisionManager = NULL;
	speed = 0.0f;
}

void BallController::moveBall(float deltaTime) {
	ball->position += speed * lastAngle * deltaTime;
}

void BallController::repelBallIfCollided() {
	if (collisionManager->hasCollided()) {
		repelBall();
	}
}

void BallController::repelBall() {
	lastAngle *= -1;
}
