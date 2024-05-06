#include "BallController.h"
#include <iostream>

BallController::BallController(PongCollisionManager* pongCollisionManager, 
	Mesh* ball, Mesh* player1, Mesh* player2, Mesh* floor, Mesh* ceiling, float ballSpeed) {
	this->pongCollisionManager = pongCollisionManager;
	this->ballSpeed = ballSpeed;

	setMeshesAndRadii(ball, player1, player2, floor, ceiling);
	generateNewRandomBallDirection();
}

BallController::~BallController() {
	player1 = NULL;
	player2 = NULL;
	ball = NULL;
	pongCollisionManager = NULL;
	ballSpeed = 0.0f;
}

void BallController::moveBall(float deltaTime) {
	ball->position += ballSpeed * ballDirection * deltaTime;
}

void BallController::bounceBallIfCollided() {
	if (pongCollisionManager->hasBallCollidedMesh(floor) || pongCollisionManager->hasBallCollidedMesh(ceiling)) {
		bounceBallOfWall();

		// when ball glitches and goes beyond walls:
		// new position = wall center + wall radius + ball radius + small error (so collision doesn't happen)
		if (ball->position.y < -0.95) {
			ball->position.y = -0.95 + ballRadius.y + wallRadius + 0.01;
		}
		else if (ball->position.y > 0.95) {
			ball->position.y = 0.95 - ballRadius.y - wallRadius - 0.01;
		}
	}
	if (pongCollisionManager->hasBallCollidedMesh(player1)) {
		bounceBallOfPlayer1();

		// when ball glitches and goes beyond player1:
		// new position = paddle center + paddle radius + ball radius + small error (so collision doesn't happen)
		if (ball->position.x < -0.9) {
			ball->position.x = -0.9 + ballRadius.x + player1Radius + 0.01;
		}
	}
	if (pongCollisionManager->hasBallCollidedMesh(player2)) {
		bounceBallOfPlayer2();

		// when ball glitches and goes beyond player2:
		// new position = paddle center + paddle radius + ball radius + small error (so collision doesn't happen)
		if (ball->position.x > 0.9) {
			ball->position.x = 0.9 - ballRadius.x - player2Radius - 0.01;
		}
	}
}

void BallController::bounceBallOfWall() {
	ballDirection.y *= -1;
}

void BallController::bounceBallOfPlayer1() {
	float player1MaxY = player1->position.y + player1Radius;

	// normalize paddle scale to (-1, 1): (y - yMin) / (yMax - yMin)
	float normalizedPos = (ball->position.y - player1->position.y) / (player1MaxY - player1->position.y);
	ballDirection = glm::vec3(1, normalizedPos, 0);
}

void BallController::bounceBallOfPlayer2() {
	float player2MaxY = player2->position.y + player2Radius;

	// normalize paddle scale to (-1, 1): (y - yMin) / (yMax - yMin)
	float normalizedPos = (ball->position.y - player2->position.y) / (player2MaxY - player2->position.y);
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
	int angleX = distribution(gen) > 0 ? 1 : -1;

	// Generate the direction for the OY axis
	float angleY = distribution(gen);

	ballDirection = glm::vec3(angleX, angleY, 0);
}

void BallController::setMeshesAndRadii(Mesh* ball, Mesh* player1, Mesh* player2, Mesh* floor, Mesh* ceiling) {
	// meshes
	this->ball = ball;
	this->player1 = player1;
	this->player2 = player2;
	this->floor = floor;
	this->ceiling = ceiling;

	// radii
	ballRadius = glm::vec3(ball->scale.x / 2, ball->scale.y / 2, 0);
	player1Radius = player1->scale.y / 2;
	player2Radius = player2->scale.y / 2;
	// it is considered that both floor and ceiling have the same scale
	this->wallRadius = floor->scale.y / 2;
}
