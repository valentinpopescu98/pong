#include "BallController.h"
#include <iostream>

BallController::BallController(PongCollisionManager* pongCollisionManager, Mesh* ball, Mesh* player1, Mesh* player2, float speed) {
	this->pongCollisionManager = pongCollisionManager;
	this->speed = speed;

	setBallAndPlayers(ball, player1, player2);
	generateNewRandomBallDirection();
}

BallController::~BallController() {
	player1 = NULL;
	player2 = NULL;
	ball = NULL;
	pongCollisionManager = NULL;
	speed = 0.0f;
}

void BallController::moveBall(float deltaTime) {
	ball->position += speed * ballDirection * deltaTime;
}

void BallController::bounceBallIfCollided() {
	if (pongCollisionManager->hasCollidedWall()) {
		bounceBallOfWall();
	}
	if (pongCollisionManager->hasCollidedPlayer1()) {
		bounceBallOfPlayer1();
	}
	if (pongCollisionManager->hasCollidedPlayer2()) {
		bounceBallOfPlayer2();
	}
}

void BallController::bounceBallOfWall() {
	ballDirection.y *= -1;
}

void BallController::bounceBallOfPlayer1() {
	float paddleRadius = player1->scale.y / 2;
	float paddleMax = player1->position.y + paddleRadius;

	// normalize paddle scale to (-1, 1): (y - yMin) / (yMax - yMin)
	float normalizedPos = (ball->position.y - player1->position.y) / (paddleMax - player1->position.y);
	ballDirection = glm::vec3(1, normalizedPos, 0);
}

void BallController::bounceBallOfPlayer2() {
	float paddleRadius = player2->scale.y / 2;
	float paddleMax = player2->position.y + paddleRadius;

	// normalize paddle scale to (-1, 1): (y - yMin) / (yMax - yMin)
	float normalizedPos = (ball->position.y - player2->position.y) / (paddleMax - player2->position.y);
	ballDirection = glm::vec3(-1, normalizedPos, 0);
}

void BallController::generateNewRandomBallDirection() {
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
}

void BallController::setBallAndPlayers(Mesh* ball, Mesh* player1, Mesh* player2) {
	this->ball = ball;
	this->player1 = player1;
	this->player2 = player2;
}
