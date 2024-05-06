#pragma once
#include "Utils.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh {
	public:
		// Create mesh from origin
		Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices,
			glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, bool isCollidable);
		// Create from parent position
		Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices, Mesh& parent,
			glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color, bool isCollidable);
		// Delete buffers
		~Mesh();
		void render(GLuint shaderId);

		// Mesh data
		std::vector<VertexStruct> vertices;
		std::vector<GLuint> indices;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 color;

		bool isCollidable;
	private:
		// Render data
		VAO* vao;
		VBO* vbo;
		EBO* ebo;
};