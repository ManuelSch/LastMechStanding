#include <iostream>
#include <memory>
#include <sstream>
#include <glew.h>
#include <glfw3.h>

#include "./Resources/Shader.h"
using namespace cgue;

#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


#include "./Scene/Cube.h"
using namespace cgue::scene;


using namespace std;


void init(GLFWwindow* window);
void update(float time_delta);
void draw();
void cleanup();
void APIENTRY debug_callback_proc(GLenum source, GLenum type, GLuintid, GLenumseverity,	GLsizeilength, constGLchar* message, GLvoid* user_param);

unique_ptr<Shader> shader;
unique_ptr<Cube> cube;


int main(int argc, char** argv) {

	// initialize glfw library:
	if (!glfwInit()) {
		cerr << "ERROR: Could not init glfw" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// display dimensions:
	int width = 800;
	int height = 600;
	bool fullscreen = false;

	if (argc >= 3) {
		cout << "You are executing '" << argv[0] << "'" << endl;

		if ((stringstream(argv[1]) >> width).fail()) {
			cerr << "ERROR: Could not parse first command-line-argument as integer." << endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}

		if ((stringstream(argv[2]) >> height).fail()) {
			cerr << "ERROR: Could not parse second command-line-argument as integer." << endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}

		if (argc >= 4) {
			if ((std::stringstream(argv[3]) >> fullscreen).fail()) {
				cerr << "ERROR: Could not parse third command-line-argument as boolean." << endl;
				system("PAUSE");
				exit(EXIT_FAILURE);
			}
		}
	}


	// define which opengl version to use (e.g. 4.1):
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// deactivate deprecated fixed function pipeline:
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// set debug context (so the debug callback is used):
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


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
		cerr << "ERROR: Could not open window" << endl;
		glfwTerminate();
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// define the window as active:
	glfwMakeContextCurrent(window);

	// initialize glew:
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cerr << "ERROR: Could not initialize glew" << endl;
		glfwTerminate();
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// define which debug callback function will be called in case of an error:
	glDebugMessageCallback(debug_callback_proc, nullptr);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	// initialize the window:
	init(window);

	// define clear color and viewport dimensions:
	glClearColor(0.35f, 0.36f, 0.43f, 0.3f);
	glViewport(0, 0, width, height);

	// for calculating the fps
	auto time = glfwGetTime();

	// keep window open as long as isn't closed manually:
	while (!glfwWindowShouldClose(window)) {

		// calculate and output the fps:
		auto time_new = glfwGetTime();
		auto time_delta = (float)(time_new - time);
		time = time_new;
		cout << "frame time: " << time_delta*1000 << "ms \t= " << 1.0/time_delta << "fps" << endl;

		// show clear color:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Game loop: update game logic and render the current frame:
		update(time_delta);
		draw();


		glfwSwapBuffers(window);
		glfwPollEvents();

		// close window if the Esc button is pressed:
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	cleanup();

	// close glfw library:
	glfwTerminate();

	return EXIT_SUCCESS;
}



void init(GLFWwindow* window) {

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowTitle(window, "Window title");

	shader = make_unique<Shader>("./tutorial/Shader/vbo_vao.vert", "./tutorial/Shader/vbo_vao.frag");
	cube = make_unique<Cube>(glm::mat4(1.0f), shader.get());

	shader->useShader();

	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);

	auto projection = glm::perspective(60.0f, width / (float)height, 0.1f, 20.0f);
	auto view = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
	auto view_projection = projection * view;

	auto view_projection_location = glGetUniformLocation(shader->programHandle, "VP");

	glUniformMatrix4fv(view_projection_location, 1, GL_FALSE, glm::value_ptr(view_projection));
}

void update(float time_delta) {
	cube->update(time_delta);
}

void draw() {
	auto& model = cube->modelMatrix;
	auto model_location = glGetUniformLocation(shader->programHandle, "model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

	shader->useShader();
	cube->draw();
}

void cleanup() {
	shader.reset(nullptr);
	cube.reset(nullptr);
}

void APIENTRY debug_callback_proc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* user_param) {
	
	stringstream ss;

	ss << "Source: ";
	if (source == GL_DEBUG_SOURCE_API)						ss << "OpenGL";
	else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM)		ss << "Windows";
	else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER)		ss << "Shader Compiler";
	else if (source == GL_DEBUG_SOURCE_THIRD_PARTY)			ss << "Third Party";
	else if (source == GL_DEBUG_SOURCE_APPICATION)			ss << "Application";
	else if (source == GL_DEBUG_SOURCE_OTHERS)				ss << "Other";
	else													ss << "Unknown";

	ss << ", Type: ";
	if (type == GL_DEBUG_TYPE_ERROR)						ss << "Error";
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)		ss << "Deprecated behavior";
	else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)		ss << "Undefined behavior";
	else if (type == GL_DEBUG_TYPE_PORTABILITY)				ss << "Portability";
	else if (type == GL_DEBUG_TYPE_PERFORMANCE)				ss << "Performance";
	else if (type == GL_DEBUG_TYPE_OTHER)					ss << "Other";
	else if (type == GL_DEBUG_TYPE_MARKER)					ss << "Marker";
	else if (type == GL_DEBUG_TYPE_PUSH_GROUP)				ss << "Push group";
	else if (type == GL_DEBUG_TYPE_POP_GROUP)				ss << "Pop group";
	else													ss << "Unknown";

	ss << ", Severity: ";
	if (severity == GL_DEBUG_SEVERITY_HIGH)					ss << "High";
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM)			ss << "Medium";
	else if (severity == GL_DEBUG_SEVERITY_LOW)				ss << "Low";
	else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)	ss << "Notification";
	else													ss << "Unknown";

	ss << ", ID: " << id;

	ss << ", Message: " << message;

	cerr << ss << endl;

}