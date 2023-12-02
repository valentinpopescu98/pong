#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	// Store VS and FS source code in two strings
	std::string vertexCode = Utils::GetFileContents(vertexShaderPath); 
	std::string fragmentCode = Utils::GetFileContents(fragmentShaderPath);

	// Convert the VS and FS code into a recognizable format by GLAD (zero-terminated array of characters)
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create VS object
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Attach VS source code to VS object
	glCompileShader(vertexShader); // Compile VS into machine code
	// Check for errors for VS
	if (checkErrors(vertexShader, "VERTEX"))
	{
		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create FS object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Attach FS source code to FS object
	glCompileShader(fragmentShader); // Compile FS into machine code
	// Check for errors for FS
	if (checkErrors(fragmentShader, "FRAGMENT"))
	{
		return;
	}

	id = glCreateProgram(); // Create final object shader
	glAttachShader(id, vertexShader); // Attach VS to the new shader
	glAttachShader(id, fragmentShader); // Attach FS to the new shader
	glLinkProgram(id); // Link final shader into the shading program
	// Check for error for the main shader
	if (checkErrors(id, "PROGRAM"))
	{
		return;
	}

	glDeleteShader(vertexShader); // Delete VS object
	glDeleteShader(fragmentShader); // Delete FS object
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id); // Use shader
}

int Shader::checkErrors(GLuint shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << std::endl;
			std::cout << infoLog << std::endl;

			if (type == "VERTEX")
			{
				std::cout << "FAULTY SHADER AT: " << vertexShaderPath << std::endl << std::endl;
				return -1;
			}
			else if (type == "FRAGMENT")
			{
				std::cout << "FAULTY SHADER AT: " << fragmentShaderPath << std::endl << std::endl;
				return -2;
			}
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << std::endl << std::endl;
			std::cout << infoLog << std::endl;
			return -3;
		}
	}

	return 0;
}