#pragma once
#include "VBO.h"

class VAO {
	public:
		VAO();
		~VAO();
		void bind();
		void unbind();
		void linkVBO(VBO* vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr);

		GLuint id;
};
