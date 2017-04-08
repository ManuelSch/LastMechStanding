#pragma once

#include ".\commonHeader.h"

class Shader {
public:
	Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	~Shader();

	void useShader();

	GLuint shaderProgram;
private:
	void loadShader(const std::string& filePath, GLenum type, GLuint& shader);

	GLuint vertexShader;
	GLuint fragmentShader;
};

