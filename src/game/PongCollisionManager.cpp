#include "PongCollisionManager.h"

PongCollisionManager::PongCollisionManager(Mesh* ball, float overlapError)
	: CollisionManager() {
	setCollidables(ball);
	this->overlapError = overlapError;

	// set an error to compensate for movement inside the rectangles between processing
	ballRadius = ball->scale.x / 2;
}

PongCollisionManager::~PongCollisionManager() {
	this->ball = NULL;

	this->overlapError = 0;
	this->ballRadius = 0;
}

bool PongCollisionManager::hasBallCollidedMesh(Mesh* mesh) {
	return mesh->isCollidable && 
		CollisionManager::hasCircleCollidedAABB(mesh->position, mesh->scale, ball->position, ballRadius, overlapError);
}

void PongCollisionManager::setCollidables(Mesh* ball) {
	this->ball = ball;
}
