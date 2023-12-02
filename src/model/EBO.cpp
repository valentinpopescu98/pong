#include "EBO.h"

EBO::EBO(std::vector<GLuint> indices) {
	glGenBuffers(1, &id); // Create a EBO buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); //Bind EBO buffer to EBO target
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); // Send indices to EBO
}

EBO::~EBO() {
	glDeleteBuffers(1, &id); // Delete EBO
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); // Bind EBO buffer to EBO target
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind EBO
}