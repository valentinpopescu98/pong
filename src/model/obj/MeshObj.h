#pragma once
#include "Utils.h"
#include "VAO_Obj.h"
#include "VBO_Obj.h"
#include "../EBO.h"

class MeshObj {
	public:
		// Create mesh from origin
		MeshObj(std::vector<ObjVertexStruct> vertices, std::vector<GLuint> indices,
			glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, bool isCollidable);
		// Create from parent position
		MeshObj(std::vector<ObjVertexStruct> vertices, std::vector<GLuint> indices, MeshObj& parent,
			glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, bool isCollidable);
		// Delete buffers
		~MeshObj();
		void render(GLuint shaderId);

		// Mesh data
		std::vector<ObjVertexStruct> vertices;
		std::vector<GLuint> indices;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 color;

		bool isCollidable;
	private:
		// Render data
		VAO_Obj* vao;
		VBO_Obj* vbo;
		EBO* ebo;
};