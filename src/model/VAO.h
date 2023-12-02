#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
