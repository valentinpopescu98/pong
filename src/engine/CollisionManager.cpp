#include "CollisionManager.h"

CollisionManager::CollisionManager(Mesh* floor, Mesh* ceiling, Mesh* player1, Mesh* player2, Mesh* ball) {
	this->floor = floor;
	this->ceiling = ceiling;
	this->player1 = player1;
	this->player2 = player2;
	this->ball = ball;

	// set an error to compensate for movement inside the rectangles between processing
	overlapError = 0.03;
}

CollisionManager::~CollisionManager() {
	this->floor = NULL;
	this->ceiling = NULL;
	this->player1 = NULL;
	this->player2 = NULL;
	this->ball = NULL;

	overlapError = 0;
}

bool CollisionManager::hasCollided() {
	float ballRadius = ball->scale.x / 2;

	return hasCollidedMesh(floor->position, floor->scale, ball->position, ballRadius) ||
		hasCollidedMesh(ceiling->position, ceiling->scale, ball->position, ballRadius) ||
		hasCollidedMesh(player1->position, player1->scale, ball->position, ballRadius) ||
		hasCollidedMesh(player2->position, player2->scale, ball->position, ballRadius);
}

bool CollisionManager::hasCollidedMesh(glm::vec3 playerPos, glm::vec3 playerScale, glm::vec3 ballPos, float ballRadius) {
	glm::vec3 playerMin = glm::vec3(playerPos.x - playerScale.x / 2, playerPos.y - playerScale.y / 2, 0);
	glm::vec3 playerMax = glm::vec3(playerPos.x + playerScale.x / 2, playerPos.y + playerScale.y / 2, 0);

	// get rectangle's closest point to circle center by clamping
	glm::vec3 playerPoint = glm::vec3(
		std::max(playerMin.x, std::min(ballPos.x, playerMax.x)),
		std::max(playerMin.y, std::min(ballPos.y, playerMax.y)),
		0
	);

	float distanceToPlayer = glm::sqrt(
		glm::pow(ballPos.x - playerPoint.x, 2) +
		glm::pow(ballPos.y - playerPoint.y, 2)
	);

	return distanceToPlayer <= ballRadius + overlapError;
}
