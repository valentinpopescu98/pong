#include "PongCollisionManager.h"

PongCollisionManager::PongCollisionManager(MeshObj* ball, float overlapError)
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

bool PongCollisionManager::hasBallCollidedMesh(MeshObj* mesh) {
	return mesh->isCollidable && 
		CollisionManager::hasCircleCollidedAABB(mesh->position, mesh->scale, ball->position, ballRadius, overlapError);
}

void PongCollisionManager::setCollidables(MeshObj* ball) {
	this->ball = ball;
}
