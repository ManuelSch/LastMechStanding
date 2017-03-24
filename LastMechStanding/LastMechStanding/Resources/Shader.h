#pragma once

// C++ Libraries:
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

// OpenGL Libraries:
#include <glew.h>
#include <glfw3.h>

namespace resources {
	class Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();

		void useShader() const;

		GLuint programHandle;

	private:
		void loadShader(const std::string& shader, GLenum shaderType, GLuint& handle);

		void link();

		GLuint vertexHandle;
		GLuint fragmentHandle;
	};
}

