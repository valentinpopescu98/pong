#pragma once
#include "VBO_Obj.h"

class VAO_Obj {
	public:
		VAO_Obj();
		~VAO_Obj();
		void bind();
		void unbind();
		void linkVBO(VBO_Obj* vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr);

		GLuint id;
};
