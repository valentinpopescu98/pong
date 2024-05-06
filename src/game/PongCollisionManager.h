#pragma once
#include "engine/CollisionManager.h"
#include "model/Mesh.h"

class PongCollisionManager : public CollisionManager {
	public:
		PongCollisionManager(Mesh* ball, float overlapError);
		~PongCollisionManager();
		bool hasBallCollidedMesh(Mesh* mesh);
		void setCollidables(Mesh* ball);
	private:
		Mesh* ball;
		float ballRadius;
		float overlapError;
};
