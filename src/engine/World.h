#pragma once
#include <vector>

#include "model/obj/MeshObj.h"
#include "Shader.h"

class World {
	public:
		World(GLuint shaderId);
		~World();
		void render();

		MeshObj *floor, *ceiling;
		std::vector<MeshObj*> middle;
		MeshObj *player1, *player2;
		MeshObj *ball;
	private:
		GLuint shaderId;
};
