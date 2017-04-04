// C++ Libraries:
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

// OpenGL Libraries:
#include <gl/glew.h>
#include <glfw3.h>

// game specific includes:
#include ".\Game\gameloop.h"


using namespace std;


// function prototypes:
void showFatalErrorMessage(string message);
void init(GLFWwindow* window);


/*
 * MAIN PROGRAM
 */
int main(int argc, char** argv) {

	// standard display dimensions (used if program arguments are null):
	int width = 800;
	int height = 600;
	bool fullscreen = false;

	// get display configuration from program arguments:
	if (argc >= 3) {
		cout << "You are executing '" << argv[0] << "'" << endl;

		if ((stringstream(argv[1]) >> width).fail()) {
			showFatalErrorMessage("Could not parse first command-line-argument as integer");
		}

		if ((stringstream(argv[2]) >> height).fail()) {
			showFatalErrorMessage("Could not parse second command-line-argument as integer");
		}

		if (argc >= 4 && (std::stringstream(argv[3]) >> fullscreen).fail()) {
			showFatalErrorMessage("Could not parse third command-line-argument as boolean");
		}
	}


	// initialize glfw library:
	if (!glfwInit()) {
		showFatalErrorMessage("Could not initialize glfw");
	}

	// define which opengl version to use (e.g. 4.1):
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// deactivate deprecated fixed function pipeline:
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Set refresh rate (important for beamer):
	GLFWmonitor* monitor = nullptr;

	if (fullscreen) {
		monitor = glfwGetPrimaryMonitor();

		auto refresh_rate = 60;
		glfwWindowHint(GLFW_REFRESH_RATE, refresh_rate);
	}

	// create new window:
	auto window = glfwCreateWindow(width, height, "", monitor, nullptr);
	if (!window) {
		glfwTerminate();
		showFatalErrorMessage("Could not open window");
	}

	// define the window as active:
	glfwMakeContextCurrent(window);


	// initialize glew library:
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		showFatalErrorMessage("Could not initialize glew");
	}


	// Create, initialize and run gameloop:
	game::Gameloop loop = game::Gameloop(window);
	loop.run();


	// close glfw library:
	glfwTerminate();

	return EXIT_SUCCESS;
}


// FATAL ERROR
// shows an error message and shuts down the program afterwards
void showFatalErrorMessage(string message) {
	cerr << "ERROR: " << message << endl;
	system("PAUSE");
	exit(EXIT_FAILURE);
}