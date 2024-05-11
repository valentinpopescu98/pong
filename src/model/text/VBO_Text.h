#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Utils.h"

class VBO_Text {
	public:
		VBO_Text(std::vector<TextVertexStruct> vertices);
		~VBO_Text();
		void bind();
		void unbind();

		GLuint id;
};
