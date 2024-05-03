#pragma once
#include "engine/CollisionManager.h"
#include "model/Mesh.h"

class PongCollisionManager : public CollisionManager {
	public:
		PongCollisionManager(Mesh* floor, Mesh* ceiling, Mesh* player1, Mesh* player2, Mesh* ball, float overlapError);
		~PongCollisionManager();
		bool hasCollidedWall();
		bool hasCollidedPlayer1();
		bool hasCollidedPlayer2();
		void setCollidables(Mesh* floor, Mesh* ceiling, Mesh* player1, Mesh* player2, Mesh* ball);
	private:
		Mesh* floor;
		Mesh* ceiling;
		Mesh* player1;
		Mesh* player2;
		Mesh* ball;
		float ballRadius;
		float overlapError;
};
