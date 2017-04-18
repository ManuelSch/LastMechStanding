#include ".\commonHeader.h"


#include ".\Game\Display.h"
#include ".\Game\Gameloop.h"
#include ".\Util\Shader.h"



unique_ptr<Display> display;
unique_ptr<Shader> shader;
unique_ptr<Gameloop> gameloop;


/*
* FUNCTION PROTOTYPES:
*/
// fatal error:
void showFatalErrorMessage(string message);

// input callbacks:
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);


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
	display = make_unique<Display>(width, height, fullscreen);


	// initialize glew:
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		showFatalErrorMessage("Could not initialize glew");
	}

	// create shader object:
	shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");

	// create gameloop object:
	gameloop = make_unique<Gameloop>(display.get(), shader.get());

	// set key, cursor and scrollwheel callbacks:
	glfwSetKeyCallback(display->window, key_callback);
	glfwSetCursorPosCallback(display->window, mouse_callback);
	glfwSetScrollCallback(display->window, scroll_callback);

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
	gameloop->key_callback(window, key, scancode, action, mode);
}
void mouse_callback(GLFWwindow * window, double xpos, double ypos) {
	gameloop->mouse_callback(window, xpos, ypos);
}
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
	gameloop->scroll_callback(window, xoffset, yoffset);
}