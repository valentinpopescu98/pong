#include "PongCollisionManager.h"

PongCollisionManager::PongCollisionManager(Mesh* floor, Mesh* ceiling, Mesh* player1, Mesh* player2, Mesh* ball) 
	: CollisionManager() {
	this->floor = floor;
	this->ceiling = ceiling;
	this->player1 = player1;
	this->player2 = player2;
	this->ball = ball;

	// set an error to compensate for movement inside the rectangles between processing
	ballRadius = ball->scale.x / 2;
	overlapError = 0.03;
}

PongCollisionManager::~PongCollisionManager() {
	this->floor = NULL;
	this->ceiling = NULL;
	this->player1 = NULL;
	this->player2 = NULL;
	this->ball = NULL;

	ballRadius = 0;
	overlapError = 0;
}

bool PongCollisionManager::hasCollidedWall() {
	return CollisionManager::hasCircleCollidedAABB(floor->position, floor->scale, ball->position, ballRadius, overlapError) ||
		CollisionManager::hasCircleCollidedAABB(ceiling->position, ceiling->scale, ball->position, ballRadius, overlapError);
}

bool PongCollisionManager::hasCollidedPlayer1() {
	return CollisionManager::hasCircleCollidedAABB(player1->position, player1->scale, ball->position, ballRadius, overlapError);
}

bool PongCollisionManager::hasCollidedPlayer2() {
	return CollisionManager::hasCircleCollidedAABB(player2->position, player2->scale, ball->position, ballRadius, overlapError);
}
