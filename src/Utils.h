#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>

struct VertexStruct {
	glm::vec3 coords;
	glm::vec3 normals;
	glm::vec3 colors;
};

class Utils {
	public:
		static std::string GetFileContents(const char* filePath);

		static void sendMatrix4x4Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix);
		static void send3fUniform(GLuint shaderID, const char* uniform, glm::vec3 values);

		static void buildCircle(float radius, int vCount);

		static std::vector<VertexStruct> quadVertices;
		static std::vector<VertexStruct> circleVertices;
		static std::vector<GLuint> quadIndices;
		static std::vector<GLuint> circleIndices;
};
