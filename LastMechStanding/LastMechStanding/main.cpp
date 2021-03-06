#include ".\commonHeader.h"


#include ".\Game\Display.h"
#include ".\Game\Gameloop.h"
#include ".\Util\Shader.h"
#include ".\Util\Font.h"



shared_ptr<Display> display;
shared_ptr<Gameloop> gameloop;
shared_ptr<Font> font;


/*
* FUNCTION PROTOTYPES:
*/
// fatal error:
void showFatalErrorMessage(string message);

// input callbacks:
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


/*
* MAIN PROGRAM
*/
int main(int argc, char** argv)
{
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

	// initialize glfw:
	if (!glfwInit()) {
		showFatalErrorMessage("Could not initialize glfw");
	}

	// define which opengl version to use (v3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// use core profile only (deactivate deprecated fixed function pipeline):
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// initialize display:
	display = make_shared<Display>(width, height, fullscreen);


	// initialize glew:
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		showFatalErrorMessage("Could not initialize glew");
	}

	// initiliaze freetype:
	font = make_shared<Font>();

	// create gameloop object:
	gameloop = make_shared<Gameloop>(display, font);

	// set key and cursor callbacks:
	glfwSetKeyCallback(display->window, key_callback);
	glfwSetCursorPosCallback(display->window, mouse_callback);
	glfwSetMouseButtonCallback(display->window, mouse_button_callback);

	// start gameloop:
	gameloop->run();

	//glDeleteVertexArrays(1, &containerVAO);
	//glDeleteBuffers(1, &VBO);

	// clean up resources:
	glfwTerminate();

	return 0;
}


/*
* FUNCTIONS:
*/

// FATAL ERROR
// shows an error message and shuts down the program afterwards
void showFatalErrorMessage(string message) {
	cerr << "ERROR: " << message << endl;
	system("PAUSE");
	exit(EXIT_FAILURE);
}


// input callbacks:
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	gameloop->keyboardCallback(window, key, scancode, action, mode);
}
void mouse_callback(GLFWwindow * window, double xpos, double ypos) {
	gameloop->mouseCallback(window, xpos, ypos);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	gameloop->mouseButtonCallback(window, button, action, mods);
}