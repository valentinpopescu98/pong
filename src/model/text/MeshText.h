#pragma once
#include "Utils.h"
#include "VAO_Text.h"
#include "VBO_Text.h"
#include "../EBO.h"

class MeshText {
	public:
		// Create mesh from origin
		MeshText(std::vector<GLuint> indices, glm::vec2 position, glm::vec3 color, Character ch, float scale);
		// Delete buffers
		~MeshText();
		void render(GLuint shaderId);

		// Mesh data
		std::vector<TextVertexStruct> vertices;
		std::vector<GLuint> indices;

		glm::vec2 position;
		glm::vec3 color;
		float scale;
	private:
		// Render data
		VAO_Text* vao;
		VBO_Text* vbo;
		EBO* ebo;
};