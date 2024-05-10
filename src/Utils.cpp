#include "Utils.h"

// Data for a quad
std::vector<VertexStruct> Utils::quadVertices = {
	//	           COORDS		          NORMALS       TEXT COORDS        COLORS
	{glm::vec3(-0.5, -0.5, 0),  glm::vec3(-1, -1, 0), glm::vec2(0, 0), glm::vec3(0, 1, 0)}, // bottom left
	{glm::vec3( 0.5, -0.5, 0),  glm::vec3( 1, -1, 0), glm::vec2(1, 0), glm::vec3(1, 1, 1)}, // bottom right
	{glm::vec3( 0.5,  0.5, 0),  glm::vec3( 1,  1, 0), glm::vec2(1, 1), glm::vec3(1, 1, 1)}, // top right
	{glm::vec3(-0.5,  0.5, 0),  glm::vec3(-1,  1, 1), glm::vec2(0, 1), glm::vec3(0, 1, 0)}  // top left
};

std::vector<GLuint> Utils::quadIndices {
	0, 1, 2,		// bottom right triangle
	2, 3, 0			// top left triangle
};

std::vector<VertexStruct> Utils::circleVertices = {};
std::vector<GLuint> Utils::circleIndices = {};

std::string Utils::getFileContents(const char* filePath) {
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

void Utils::buildCircle(float radius, int vCount) {
	float angle = 360.0f / vCount;
	int triangleCount = vCount - 2;

	std::vector<glm::vec3> temp;
	// positions
	for (int i = 0; i < vCount; i++)
	{
		float currentAngle = angle * i;
		float x = radius * cos(glm::radians(currentAngle));
		float y = radius * sin(glm::radians(currentAngle));

		circleVertices.push_back({ glm::vec3(x, y, 0), glm::vec3(0, 0, 0),
			glm::vec2(0.5f + 0.5f * std::cos(angle), 0.5f + 0.5f * std::sin(angle)), glm::vec3(y - x, y, x - y) });
	}

	// push indexes of each triangle points
	for (int i = 0; i < triangleCount; i++)
	{
		circleIndices.push_back(0);
		circleIndices.push_back(i + 1);
		circleIndices.push_back(i + 2);
	}
}

void Utils::sendMatrix4x4Uniform(GLuint shaderId, const char* uniform, glm::mat4 matrix)
{
	GLuint location = glGetUniformLocation(shaderId, uniform); // Create uniform variable
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // Set matrix value for the uniform
	checkForErrors();
}

void Utils::send3fUniform(GLuint shaderId, const char* uniform, glm::vec3 values)
{
	GLuint location = glGetUniformLocation(shaderId, uniform); // Create uniform variable
	glUniform3f(location, values.x, values.y, values.z); // Set values for the uniform
	checkForErrors();
}

void Utils::send1iUniform(GLuint shaderId, const char* uniform, int value) {
	GLuint location = glGetUniformLocation(shaderId, uniform); // Create uniform variable
	glUniform1i(location, value); // Set value for the uniform
	checkForErrors();
}

void Utils::checkForErrors() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << error << std::endl;
	}
}
