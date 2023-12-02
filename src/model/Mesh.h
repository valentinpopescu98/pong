#pragma once
#include "Utils.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh {
	public:
		// Create mesh from origin
		Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices,
			glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
		// Create from parent position
		Mesh(std::vector<VertexStruct> vertices, std::vector<GLuint> indices, Mesh& parent,
			glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
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
	private:
		// Render data
		VAO* vao;
		VBO* vbo;
		EBO* ebo;
};