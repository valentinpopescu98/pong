#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model/Mesh.h"

class CollisionManager {
	public:
		CollisionManager(Mesh* player1, Mesh* player2, Mesh* ball);
		~CollisionManager();
		bool hasCollided();
	private:
		bool hasCollidedPlayer(glm::vec3 playerPos, glm::vec3 playerScale, glm::vec3 ballPos, float ballRadius);

		Mesh* player1;
		Mesh* player2;
		Mesh* ball;
		float overlapError;
};
