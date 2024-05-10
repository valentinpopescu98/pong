#pragma once
#include <ft2build.h>
#include <freetype/freetype.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <map>

#include "model/Mesh.h"
#include "Utils.h"

class Engine;

class TextRenderer {
	public:
		TextRenderer(GLuint shaderId, const char* fontPath, int fontSize);
		~TextRenderer();
		void renderText(const std::string& text, glm::vec2 pos, glm::vec2 scale, glm::vec3 color);
	private:
		void createTextures(const unsigned char* buffer, int width, int height);
		float pixelToNormalized(int pixelPos, int viewportSize);
		
		FT_Library ft;
		FT_Face face;
		std::map<GLchar, GLuint> textures;
		std::vector<Mesh*> characters;
		GLuint shaderId;
		FT_UInt fontSize;
};
