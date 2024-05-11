#include "VAO_Obj.h"

VAO_Obj::VAO_Obj() {
	glGenVertexArrays(1, &id); // Create a VAO buffer
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

VAO_Obj::~VAO_Obj() {
	glDeleteBuffers(1, &id); // Delete VBO
}

void VAO_Obj::bind() {
	glBindVertexArray(id); // Bind VBO buffer to VAO target
}

void VAO_Obj::unbind() {
	glBindVertexArray(0); // Unbind VAO
}

void VAO_Obj::linkVBO(VBO_Obj* vbo, GLuint layoutLocation, GLsizei stride, const void* startPtr) {
	vbo->bind();
	glVertexAttribPointer(layoutLocation, 3, GL_FLOAT, GL_FALSE, stride, startPtr); // Send VBOs to chosen layout location
	glEnableVertexAttribArray(layoutLocation); // Enable layout location
	vbo->unbind();
}