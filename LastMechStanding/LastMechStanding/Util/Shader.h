#pragma once

#include "..\commonHeader.h"

class Shader {
public:
	Shader(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
	~Shader();

	void useShader();
	GLint getUniformLocation(const string & uniformName);

	GLuint shaderProgram;
private:
	void loadShader(const string& filePath, GLenum type, GLuint& shader);

	GLuint vertexShader;
	GLuint fragmentShader;
};

