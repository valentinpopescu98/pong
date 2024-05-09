#pragma once
#include <vector>

#include "model/Mesh.h"
#include "Shader.h"

class World {
	public:
		World(GLuint shaderId);
		~World();
		void render();
		GLuint getShaderId();

		Mesh *floor, *ceiling;
		std::vector<Mesh*> middle;
		Mesh *player1, *player2;
		Mesh *ball;
	private:
		GLuint shaderId;
};
