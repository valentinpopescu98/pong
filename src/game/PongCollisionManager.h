#pragma once
#include "engine/CollisionManager.h"
#include "model/obj/MeshObj.h"

class PongCollisionManager : public CollisionManager {
	public:
		PongCollisionManager(MeshObj* ball, float overlapError);
		~PongCollisionManager();
		bool hasBallCollidedMesh(MeshObj* mesh);
		void setCollidables(MeshObj* ball);
	private:
		MeshObj* ball;
		float ballRadius;
		float overlapError;
};
