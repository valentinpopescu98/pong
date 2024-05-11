#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Utils.h"

class VBO_Obj {
	public:
		VBO_Obj(std::vector<ObjVertexStruct> vertices);
		~VBO_Obj();
		void bind();
		void unbind();

		GLuint id;
};
