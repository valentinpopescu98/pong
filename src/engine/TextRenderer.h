#pragma once
#include <ft2build.h>
#include <freetype/freetype.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <map>

#include "model/text/MeshText.h"
#include "Utils.h"

class Engine;

class TextRenderer {
	public:
		TextRenderer(GLuint shaderId, const char* fontPath, int fontSize);
		~TextRenderer();
		void renderText(std::string text, glm::vec2 position, glm::vec3 color, float scale);
	private:
		void createTextures();
		
		FT_Library ft;
		FT_Face face;
		std::map<char, Character> characters;
		GLuint shaderId;
};
