#include "Display.h"


Display::Display(int _width, int _height, bool _fullscreen) : width(_width), height(_height), fullscreen(_fullscreen)
{
	// Set refresh rate (important for beamer):
	GLFWmonitor* monitor = nullptr;
	if (this->fullscreen) {
		monitor = glfwGetPrimaryMonitor();
		auto refresh_rate = 60;
		glfwWindowHint(GLFW_REFRESH_RATE, refresh_rate);
	}

	// make window non resizable:
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// create new window:
	this->window = glfwCreateWindow(width, height, "Last Mech Standing", nullptr, nullptr);
	if (this->window == nullptr)
	{
		glfwTerminate();
		cerr << "ERROR: Could not open glfw window" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// define the window as active:
	glfwMakeContextCurrent(window);

	// set viewport size:
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

Display::~Display()
{
}
