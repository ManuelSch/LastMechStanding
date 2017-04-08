#include "Shader.h"

Shader::Shader(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath) {

	// create shader program:
	shaderProgram = glCreateProgram();

	// load shader source code:
	loadShader(vertexShaderFilePath, GL_VERTEX_SHADER, vertexShader);
	loadShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER, fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::useShader() {
	glUseProgram(shaderProgram);
}

void Shader::loadShader(const std::string & filePath, GLenum type, GLuint & shader) {

	std::ifstream shaderFile(filePath);

	if (shaderFile.good()) {
		// read source code from shader file:
		std::string code = std::string(std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>());

		shaderFile.close();

		// create shader object:
		shader = glCreateShader(type);

		// attach source code to the shader object and compile:
		auto codePtr = code.c_str();
		glShaderSource(shader, 1, &codePtr, NULL);
		glCompileShader(shader);

		// check if shader compilation was successful:
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR: Shader compilation failed:\n" << infoLog << std::endl;
		}

		//  attach shader to program object and link it:
		glAttachShader(shaderProgram, shader);
		glLinkProgram(shaderProgram);

		// check if program linking was successful:
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR: Shader linking failed:\n" << infoLog << std::endl;
		}
	}
}
