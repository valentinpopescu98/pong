#include "World.h"

World::World() {
	// Create shaders
	programShader = new Shader("src/shader/vert.glsl", "src/shader/frag.glsl");
	programShader->use();

	middle.resize(10, nullptr);
	for (size_t i = 0; i < middle.size(); i++) {
		middle[i] = new Mesh(Utils::quadVertices, Utils::quadIndices,
			glm::vec3(0, -0.9 + i / 5.0f, 0), glm::vec3(0, 0, 0), glm::vec3(0.05, 0.1, 0), glm::vec3(1, 1, 1), false);
	}

	floor = new Mesh(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(0, -0.95, 0), glm::vec3(0, 0, 0), glm::vec3(1.9, 0.05, 0), glm::vec3(1, 1, 1), true);
	ceiling = new Mesh(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(0, 0.95, 0), glm::vec3(0, 0, 0), glm::vec3(1.9, 0.05, 0), glm::vec3(1, 1, 1), true);

	player1 = new Mesh(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(-0.9, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.05, 0.3, 0), glm::vec3(1, 0, 0), true);
	player2 = new Mesh(Utils::quadVertices, Utils::quadIndices,
		glm::vec3(0.9, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.05, 0.3, 0), glm::vec3(0, 0, 1), true);

	Utils::buildCircle(1, 24);
	// color = vec3(0), hence the ball will be colored with vertex data
	ball = new Mesh(Utils::circleVertices, Utils::circleIndices,
		glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.04, 0.05, 0), glm::vec3(0, 0, 0), true);
}

World::~World() {
	delete floor, ceiling, player1, player2, ball;
	for (Mesh* barrier : middle) {
		delete barrier;
	}
	delete programShader;
}

void World::render() {
	for (Mesh* barrier : middle) {
		barrier->render(programShader->id);
	}
	floor->render(programShader->id);
	ceiling->render(programShader->id);
	player1->render(programShader->id);
	player2->render(programShader->id);
	ball->render(programShader->id);
}

GLuint World::getShaderId() {
	return programShader->id;
}
