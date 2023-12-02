#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Utils.h"

class VBO {
	public:
		VBO(std::vector<VertexStruct> vertices);
		~VBO();
		void bind();
		void unbind();

		GLuint id;
};
