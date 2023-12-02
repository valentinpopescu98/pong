#include "VBO.h"

VBO::VBO(std::vector<VertexStruct> vertices) {
	glGenBuffers(1, &id); // Create a VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexStruct), &vertices[0], GL_STATIC_DRAW); // Send vertices to VBO
}

VBO::~VBO() {
	glDeleteBuffers(1, &id); // Delete VBO
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}