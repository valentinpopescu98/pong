#include "VAO_Text.h"

VAO_Text::VAO_Text() {
	glGenVertexArrays(1, &id); // Create a VAO buffer
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

VAO_Text::~VAO_Text() {
	glDeleteBuffers(1, &id); // Delete VBO
}

void VAO_Text::bind() {
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

void VAO_Text::unbind() {
	glBindVertexArray(0); // Unbind VAO
}

void VAO_Text::linkVBO(VBO_Text* vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr) {
	vbo->bind();
	glVertexAttribPointer(layoutLocation, 4, GL_FLOAT, GL_FALSE, stride, startPtr); // Send VBOs to chosen layout location
	glEnableVertexAttribArray(layoutLocation); // Enable layout location
	vbo->unbind();
}
