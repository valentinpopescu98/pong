#include "World.h"

World::World(GLuint shaderId) {
	this->shaderId = shaderId;

	middle.resize(10, nullptr);
	for (size_t i = 0; i < middle.size(); i++) {
		middle[i] = new MeshObj(Utils::quadVertices, Utils::quadIndices,
			glm::vec3(0, -0.9 + i / 5.0f, 0), glm::vec3(0, 0, 0), glm::vec3(0.05, 0.1, 0), glm::vec3(1, 1, 1), false);
	}

	floor = new MeshObj(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(0, -0.95, 0), glm::vec3(0, 0, 0), glm::vec3(1.9, 0.05, 0), glm::vec3(1, 1, 1), true);
	ceiling = new MeshObj(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(0, 0.95, 0), glm::vec3(0, 0, 0), glm::vec3(1.9, 0.05, 0), glm::vec3(1, 1, 1), true);

	player1 = new MeshObj(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(-0.9, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.05, 0.3, 0), glm::vec3(1, 0, 0), true);
	player2 = new MeshObj(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(0.9, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.05, 0.3, 0), glm::vec3(0, 0, 1), true);

	Utils::buildCircle(1, 24);
	// color = vec3(0), hence the ball will be colored with vertex data
	ball = new MeshObj(Utils::circleVertices, Utils::circleIndices,
		glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.04, 0.05, 0), glm::vec3(0, 0, 0), true);
}

World::~World() {
	delete floor, ceiling, player1, player2, ball;
	for (MeshObj* barrier : middle) {
		delete barrier;
	}
}

void World::render() {
	for (MeshObj* barrier : middle) {
		barrier->render(shaderId);
	}
	floor->render(shaderId);
	ceiling->render(shaderId);
	player1->render(shaderId);
	player2->render(shaderId);
	ball->render(shaderId);
}
