#pragma once

// C++ Libraries:
#include <iostream>

// OpenGL Libraries:
#include <glew.h>
#include <glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class gameloop
{
public:
	gameloop(GLFWwindow* _window);
	~gameloop();

	void run();

private:
	GLFWwindow* window;

	void update(float time_delta);
	void draw();
	void cleanup();
};

