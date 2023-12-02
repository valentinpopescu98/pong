#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &id); // Create a VAO buffer
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

VAO::~VAO() {
	glDeleteBuffers(1, &id); // Delete VBO
}

void VAO::bind() {
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

void VAO::unbind() {
	glBindVertexArray(0); // Unbind VAO
}

void VAO::linkVBO(VBO* vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr) {
	vbo->bind();
	glVertexAttribPointer(layoutLocation, 3, GL_FLOAT, GL_FALSE, stride, startPtr); // Send VBOs to chosen layout location
	glEnableVertexAttribArray(layoutLocation); // Enable layout location
	vbo->unbind();
}