#pragma once

#include "..\commonHeader.h"

// OpenGL Libraries:
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// game specific includes:
#include "..\Util\Shader.h"
#include "..\Scene\Cube.h"


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