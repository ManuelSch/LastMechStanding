#pragma once

// C++ Libraries:
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

// OpenGL Libraries:
#include <glew.h>
#include <glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// game specific includes:
#include "..\Resources\Shader.h"


namespace game {
	class Gameloop
	{
	public:
		Gameloop(GLFWwindow* _window);
		~Gameloop();

		void run();

	private:
		GLFWwindow* window;

		void update(float time_delta);
		void draw();
		void cleanup();
	};
}