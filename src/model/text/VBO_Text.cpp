#include "VBO_Text.h"

VBO_Text::VBO_Text(std::vector<TextVertexStruct> vertices) {
	glGenBuffers(1, &id); // Create a VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TextVertexStruct), &vertices[0], GL_DYNAMIC_DRAW); // Send vertices to VBO
}

VBO_Text::~VBO_Text() {
	glDeleteBuffers(1, &id); // Delete VBO
}

void VBO_Text::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
}

void VBO_Text::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}