#include "VBO_Obj.h"

VBO_Obj::VBO_Obj(std::vector<ObjVertexStruct> vertices) {
	glGenBuffers(1, &id); // Create a VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ObjVertexStruct), &vertices[0], GL_STATIC_DRAW); // Send vertices to VBO
}

VBO_Obj::~VBO_Obj() {
	glDeleteBuffers(1, &id); // Delete VBO
}

void VBO_Obj::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id); // Bind VBO buffer to VBO target
}

void VBO_Obj::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}