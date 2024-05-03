#include "CollisionManager.h"

bool CollisionManager::hasCircleCollidedAABB(glm::vec3 rectanglePos, glm::vec3 rectangleScale, glm::vec3 circlePos, 
	float circleRadius, float overlapError) {
	glm::vec3 rectangleMin = glm::vec3(rectanglePos.x - rectangleScale.x / 2, rectanglePos.y - rectangleScale.y / 2, 0);
	glm::vec3 rectangleMax = glm::vec3(rectanglePos.x + rectangleScale.x / 2, rectanglePos.y + rectangleScale.y / 2, 0);

	// get rectangle's closest point to circle center by clamping
	glm::vec3 rectanglePoint = glm::vec3(
		std::max(rectangleMin.x, std::min(circlePos.x, rectangleMax.x)),
		std::max(rectangleMin.y, std::min(circlePos.y, rectangleMax.y)),
		0
	);

	float distanceToPlayer = glm::sqrt(
		glm::pow(circlePos.x - rectanglePoint.x, 2) +
		glm::pow(circlePos.y - rectanglePoint.y, 2)
	);

	return distanceToPlayer <= circleRadius + overlapError;
}
