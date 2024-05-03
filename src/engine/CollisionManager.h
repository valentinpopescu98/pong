#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

class CollisionManager {
	protected:
		static bool hasCircleCollidedAABB(glm::vec3 rectanglePos, glm::vec3 rectangleScale, glm::vec3 circlePos,
			float circleRadius, float overlapError);
};
