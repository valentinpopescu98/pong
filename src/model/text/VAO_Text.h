#pragma once
#include "VBO_Text.h"

class VAO_Text {
	public:
		VAO_Text();
		~VAO_Text();
		void bind();
		void unbind();
		void linkVBO(VBO_Text* vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr);

		GLuint id;
};
