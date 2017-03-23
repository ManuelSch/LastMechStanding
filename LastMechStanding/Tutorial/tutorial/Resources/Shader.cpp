#include "Shader.h"

#include <iostream>
#include <fstream>
#include <memory>

using namespace cgue;
using namespace std;

Shader::Shader(const string& vertexShader, const string& fragmentShader) 
	: programHandle(0)
	, vertexHandle(0)
	, fragmentHandle(0) {
	programHandle = glCreateProgram();

	if (programHandle == 0) {
		cerr << "Failed to create shader program" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	cout << "1" << endl;
	loadShader(vertexShader, GL_VERTEX_SHADER, vertexHandle);
	cout << "10" << endl;
	loadShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentHandle);

	link();
}


Shader::~Shader() {
	glDeleteProgram(programHandle);
	glDeleteShader(vertexHandle);
	glDeleteShader(fragmentHandle);
}

void Shader::useShader() const {
	glUseProgram(programHandle);
}

void Shader::loadShader(const string& shader, GLenum shaderType, GLuint& handle) {
	cout << "2" << endl;
	ifstream shaderFile(shader);

	cout << "3" << endl;
	if (shaderFile.good()) {
		cout << "4" << endl;
		string code = string(istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>());

		cout << "5" << endl;
		shaderFile.close();

		cout << "6" << endl;
		handle = glCreateShader(shaderType);

		cout << "7" << endl;
		if (handle == 0) {
			cerr << "Failed to create shader" << endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}

		auto codePtr = code.c_str();
		glShaderSource(handle, 1, &codePtr, nullptr);
		glCompileShader(handle);

		GLint succeded;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &succeded);

		if (succeded == GL_FALSE || !glIsShader(handle)) {
			GLint logSize;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);

			auto message = make_unique<char[]>(logSize);
			glGetShaderInfoLog(handle, logSize, nullptr, message.get());

			cerr << "Failed to compile shader" << endl;
			cerr << message.get() << endl;
			system("PAUSE");
			message.reset(nullptr);
			exit(EXIT_FAILURE);
		}
	}
	else {
		cerr << "Failed to open shader file" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
}

void Shader::link() {
	glAttachShader(programHandle, vertexHandle);
	glAttachShader(programHandle, fragmentHandle);

	glLinkProgram(programHandle);
}
