#include "Shader.h"

Shader::Shader(const string & vertexShaderFilePath, const string & fragmentShaderFilePath) {

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

GLint Shader::getUniformLocation(const string & uniformName) {
	return glGetUniformLocation(shaderProgram, uniformName.c_str());;
}

void Shader::loadShader(const string & filePath, GLenum type, GLuint & shader) {

	ifstream shaderFile(filePath);

	if (shaderFile.good()) {
		// read source code from shader file:
		string code = string(istreambuf_iterator<char>(shaderFile), istreambuf_iterator<char>());

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
			cout << "ERROR: Shader compilation failed:\n" << infoLog << endl;
		}

		//  attach shader to program object and link it:
		glAttachShader(shaderProgram, shader);
		glLinkProgram(shaderProgram);

		// check if program linking was successful:
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			cout << "ERROR: Shader linking failed:\n" << infoLog << endl;
		}
	}
}
