#include "Gameloop.h"



Gameloop::Gameloop(Display* _display) : display(_display), camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
	// initialize member variables:
	for (GLuint i = 0; i < 1024; i++) {
		keys[i] = false;
	}

	// set initial cursor position:
	lastX = display->width / 2.0;
	lastY = display->height / 2.0;

	// hide and capture the cursor:
	glfwSetInputMode(display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// enable z-buffer:
	glEnable(GL_DEPTH_TEST);
}


Gameloop::~Gameloop()
{
}


void Gameloop::run()
{
	shared_ptr<SceneObject> newObject;

	newObject = make_shared<Character>();
	newObject->translate(glm::vec3(0.0f, -1.75f, 0.0f));
	newObject->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	sceneObjects.push_back(newObject);

	newObject = make_shared<Character>();
	newObject->translate(glm::vec3(2.0f, -1.75f, 0.0f));
	newObject->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	newObject->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(newObject);

	// frame independency:
	deltaTime = 0.0f;
	lastFrame = 0.0f;

	// game loop:
	while (!glfwWindowShouldClose(display->window))
	{
		// calculate delta time for frame independency:
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// check if any events were triggered:
		glfwPollEvents();
		do_movement();

		// clear color and depth buffers:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		* Update objects:
		*/
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->update(deltaTime);
			}
		}

		/*
		* Draw objects:
		*/
		// transformation matrices:
		glm::mat4 projection = glm::perspective(camera.zoom, (float)display->width / (float)display->height, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();

		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->draw(&view, &projection);
			}
		}


		// swap window and color buffer:
		glfwSwapBuffers(display->window);
	}
}


void Gameloop::do_movement()
{
	// camera controls:
	if (keys[GLFW_KEY_W])
		this->camera.processKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		this->camera.processKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		this->camera.processKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		this->camera.processKeyboard(RIGHT, deltaTime);
}

void Gameloop::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// esc key -> close window:
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void Gameloop::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (this->firstMouse)
	{
		this->lastX = xpos;
		this->lastY = ypos;
		this->firstMouse = false;
	}

	// calculate cursor offset since last frame:
	GLfloat xoffset = xpos - this->lastX;
	GLfloat yoffset = this->lastY - ypos; // Reversed since y-coordinates range from bottom to top
	this->lastX = xpos;
	this->lastY = ypos;

	this->camera.processMouseMovement(xoffset, yoffset);
}

void Gameloop::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	this->camera.processMouseScroll(yoffset);
}