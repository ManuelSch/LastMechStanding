#pragma once

/*
* Creates a new window and stores parameters such as width, height and the glfw window object
*/

#include "..\commonHeader.h"

class Display
{
public:
	Display(int _width, int _height, bool _fullscreen);
	~Display();

	int width, height;
	bool fullscreen;
	GLFWwindow* window;
};

