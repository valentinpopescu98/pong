#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <vector>

struct ObjVertexStruct {
	glm::vec3 coords;
	glm::vec3 normals;
	glm::vec2 textCoords;
	glm::vec3 colors;
};

struct TextVertexStruct {
	glm::vec3 coords;
	glm::vec2 textCoords;
};

struct Character {
	unsigned int textureId;  // ID handle of the glyph texture
	glm::ivec2   size;       // Size of glyph
	glm::ivec2   bearing;    // Offset from origin to left/top of glyph
	unsigned int advance;    // Offset to advance to next glyph
};

class Utils {
	public:
		static std::string getFileContents(const char* filePath);
		static void checkForErrors();
		static void buildCircle(float radius, int vCount);

		static void sendMatrix4x4Uniform(GLuint shaderId, const char* uniform, glm::mat4 matrix);
		static void send3fUniform(GLuint shaderId, const char* uniform, glm::vec3 values);
		static void send1iUniform(GLuint shaderId, const char* uniform, int value);

		static std::vector<ObjVertexStruct> quadVertices, circleVertices;
		static std::vector<TextVertexStruct> quadTextVertices;
		static std::vector<GLuint> quadIndices;
		static std::vector<GLuint> circleIndices;
};
