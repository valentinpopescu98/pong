#include "Utils.h"

// Data for a quad
std::vector<VertexStruct> Utils::quadVertices = {
	//	           COORDS		          NORMALS              COLORS
	{glm::vec3(-0.5, -0.5, 0),  glm::vec3(-1, -1, 0), glm::vec3(0, 1, 0)}, // bottom left
	{glm::vec3( 0.5, -0.5, 0),  glm::vec3( 1, -1, 0), glm::vec3(1, 1, 1)}, // bottom right
	{glm::vec3( 0.5,  0.5, 0),  glm::vec3( 1,  1, 0), glm::vec3(1, 1, 1)}, // top right
	{glm::vec3(-0.5,  0.5, 0),  glm::vec3(-1,  1, 1), glm::vec3(0, 1, 0)}  // top left
};

std::vector<GLuint> Utils::quadIndices {
	0, 1, 2,		// bottom right triangle
	2, 3, 0			// top left triangle
};

std::vector<VertexStruct> Utils::circleVertices = {};
std::vector<GLuint> Utils::circleIndices = {};

std::string Utils::GetFileContents(const char* filePath) {
	std::ifstream in(filePath, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}

	throw(errno + " ERROR: Could not open file.");
}

void Utils::sendMatrix4x4Uniform(GLuint shaderID, const char* uniform, glm::mat4 matrix)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // Set matrix value for the uniform
}

void Utils::send3fUniform(GLuint shaderID, const char* uniform, glm::vec3 values)
{
	GLuint location = glGetUniformLocation(shaderID, uniform); // Create uniform variable
	glUniform3f(location, values.x, values.y, values.z); // Set values for the uniform
}

void Utils::buildCircle(float radius, int vCount)
{
	float angle = 360.0f / vCount;

	int triangleCount = vCount - 2;

	std::vector<glm::vec3> temp;
	// positions
	for (int i = 0; i < vCount; i++)
	{
		float currentAngle = angle * i;
		float x = radius * cos(glm::radians(currentAngle));
		float y = radius * sin(glm::radians(currentAngle));
		float z = 0.0f;

		circleVertices.push_back({ glm::vec3(x, y, z), glm::vec3(x, y, z), glm::vec3(x, y, z) });
	}

	// push indexes of each triangle points
	for (int i = 0; i < triangleCount; i++)
	{
		circleIndices.push_back(0);
		circleIndices.push_back(i + 1);
		circleIndices.push_back(i + 2);
	}
}
