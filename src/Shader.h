#pragma once
#include <glm/glm.hpp>
#include <iostream>

#include "Utils.h"

class Shader {
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();
		void use();

		GLuint id;
		glm::mat4 view, projection;
	private:
		int checkErrors(GLuint shader, const char* type);

		std::string vertexShaderPath, fragmentShaderPath;
};
