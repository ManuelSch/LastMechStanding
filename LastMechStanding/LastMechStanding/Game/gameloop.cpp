#include "Gameloop.h"
using namespace game;


using namespace std;
using namespace util;
using namespace scene;


unique_ptr<util::Shader> shader;
unique_ptr<Cube> cube;


Gameloop::Gameloop(GLFWwindow* _window) {
	window = _window;

	// define clear color and viewport dimensions:
	glClearColor(0.35f, 0.36f, 0.43f, 0.3f);
	//glViewport(0, 0, width, height);

	// enable depth test:
	glEnable(GL_DEPTH_TEST);

	glfwSetWindowTitle(window, "Last Mech Standing");


	shader = make_unique<Shader>("./Resources/Shaders/vbo_vao.vert", "./Resources/Shaders/vbo_vao.frag");
	cube = make_unique<Cube>(glm::mat4(1.0f), shader.get());


	shader->useShader();


	// perspective projection:
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);

	auto projection = glm::perspective(60.0f, width / (float)height, 0.1f, 20.0f);
	auto view = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
	auto view_projection = projection * view;

	auto view_projection_location = glGetUniformLocation(shader->programHandle, "VP");

	glUniformMatrix4fv(view_projection_location, 1, GL_FALSE, glm::value_ptr(view_projection));
}


Gameloop::~Gameloop() {
}


void Gameloop::run() {

	bool running = true;

	// for calculating the fps
	auto time = glfwGetTime();

	// keep window open as long as isn't closed manually:
	while (running && !glfwWindowShouldClose(window)) {

		// clear the frame and depth buffer:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// calculate and output the fps:
		auto time_new = glfwGetTime();
		auto time_delta = (float)(time_new - time);
		time = time_new;
		cout << "frame time: " << time_delta * 1000 << "ms \t= " << 1.0 / time_delta << "fps" << endl;

		// fetch user inputs:
		glfwPollEvents();
		running = !glfwGetKey(window, GLFW_KEY_ESCAPE);

		// update game logic: 
		update(time_delta);

		// render the current frame:
		draw();
		glfwSwapBuffers(window);

		// check for errors:
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			switch (error) {
			case GL_INVALID_ENUM:
				cerr << "GL: enum argument out of range." << endl;
				break;
			case GL_INVALID_VALUE:
				cerr << "GL: Numeric argument out of range." << endl;
				break;
			case GL_INVALID_OPERATION:
				cerr << "GL: Operation illegal in current state." << endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				cerr << "GL: Framebuffer object is not complete." << endl;
				break;
			case GL_OUT_OF_MEMORY:
				cerr << "GL: Not enough memory left to execute command." << endl;
				break;
			default:
				cerr << "GL: Unknown error." << endl;
			}
		}
	}

	glfwSetWindowShouldClose(window, true);

	cleanup();
}


void Gameloop::cleanup() {
	shader.reset(nullptr);

	// TODO: Reset all objects here:
	cube.reset(nullptr);
}


void Gameloop::update(float time_delta) {
	// TODO: update the game logic and all scene objects here:
	cube->update(time_delta);
}


void Gameloop::draw() {
	// TODO: draw all objects here:
	auto& model = cube->modelMatrix;
	auto model_location = glGetUniformLocation(shader->programHandle, "model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

	shader->useShader();
	cube->draw();
}
