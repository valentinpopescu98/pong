#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model/Mesh.h"

class CollisionManager {
	public:
		CollisionManager(Mesh* floor, Mesh* ceiling, Mesh* player1, Mesh* player2, Mesh* ball);
		~CollisionManager();
		bool hasCollidedWall();
		bool hasCollidedPlayer1();
		bool hasCollidedPlayer2();
	private:
		bool hasCollidedMesh(glm::vec3 meshPos, glm::vec3 meshScale, glm::vec3 ballPos, float ballRadius);

		Mesh* floor;
		Mesh* ceiling;
		Mesh* player1;
		Mesh* player2;
		Mesh* ball;
		float overlapError;
		float ballRadius;
};
