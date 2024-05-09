#pragma once
#include <vector>

#include "model/Mesh.h"
#include "Shader.h"

class World {
	public:
		World();
		~World();
		void render();
		GLuint getShaderId();

		Mesh *floor, *ceiling;
		std::vector<Mesh*> middle;
		Mesh *player1, *player2;
		Mesh *ball;
	private:
		//std::vector<Mesh> environment;
		Shader *programShader;
};
