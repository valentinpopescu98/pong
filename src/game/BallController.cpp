#include "BallController.h"
#include <iostream>

BallController::BallController(CollisionManager* collisionManager, Mesh* ball, Mesh* player1, Mesh* player2, float speed) {
	this->collisionManager = collisionManager;
	this->ball = ball;
	this->player1 = player1;
	this->player2 = player2;
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

	ballDirection = glm::vec3(angleX, angleY, 0);
	//ballDirection = glm::vec3(1, 1, 0);
}

BallController::~BallController() {
	player1 = NULL;
	player2 = NULL;
	ball = NULL;
	collisionManager = NULL;
	speed = 0.0f;
}

void BallController::moveBall(float deltaTime) {
	ball->position += speed * ballDirection * deltaTime;
}

void BallController::bounceBallIfCollided() {
	if (collisionManager->hasCollidedWall()) {
		bounceBallOfWall();
	}
	if (collisionManager->hasCollidedPlayer1()) {
		bounceBallOfPlayer1();
	}
	if (collisionManager->hasCollidedPlayer2()) {
		bounceBallOfPlayer2();
	}
}

void BallController::bounceBallOfWall() {
	ballDirection.y *= -1;
}

void BallController::bounceBallOfPlayer1() {
	if (ball->position.y > player1->position.y) {
		ballDirection = glm::vec3(1, 1, 0);
	} else if (ball->position.y < player1->position.y) {
		ballDirection = glm::vec3(1, -1, 0);
	} else {
		ballDirection = glm::vec3(1, 0, 0);
	}
}

void BallController::bounceBallOfPlayer2() {
	if (ball->position.y > player2->position.y) {
		ballDirection = glm::vec3(-1, 1, 0);
	} else if (ball->position.y < player2->position.y) {
		ballDirection = glm::vec3(-1, -1, 0);
	} else {
		ballDirection = glm::vec3(-1, 0, 0);
	}
}
