#pragma once
#include <vector>

#include "model/Mesh.h"
#include "Shader.h"

class World {
	public:
		World();
		~World();
		void render();

		Mesh* player1;
		Mesh* player2;
	private:
		Mesh* ball;
		//std::vector<Mesh> environment;
		Shader* programShader;
};

