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
	shared_ptr<SceneObject> player;
	shared_ptr<SceneObject> enemy;

	player = make_shared<Character>();
	player->translate(glm::vec3(0.0f, -1.75f, 0.0f));
	player->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	sceneObjects.push_back(player);

	enemy = make_shared<Character>();
	enemy->translate(glm::vec3(2.0f, -1.75f, 0.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);

	enemy = make_shared<Character>();
	enemy->translate(glm::vec3(5.0f, -1.75f, 0.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);

	enemy = make_shared<Character>();
	enemy->translate(glm::vec3(5.0f, -1.75f, 3.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);

	enemy = make_shared<Character>();
	enemy->translate(glm::vec3(-5.0f, -1.75f, 3.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);


	// sunlight:
	shared_ptr<LightSource> sunLight = make_shared<LightSource>(LightSource::DIRECTIONAL);
	sunLight->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	sunLight->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	sunLight->diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	sunLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	lightSources.push_back(sunLight);
	


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
		do_movement(player);

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
				int r = (i & 0x000000FF) >> 0;
				int g = (i & 0x0000FF00) >> 8;
				int b = (i & 0x00FF0000) >> 16;
				sceneObjects[i]->pickingColor = glm::vec4(r/255.0f, g / 255.0f, b / 255.0f, 1.0f);
				sceneObjects[i]->draw(&view, &projection, &camera, &lightSources);
			}
		}

		glFlush();
		glFinish();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		unsigned char data[4];
		glReadPixels(display->width / 2, display->height / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
		int pickedID =
			data[0] +
			data[1] * 256 +
			data[2] * 256 * 256;
		if (pickedID == 5000243) {
			cout << "background" << endl;
		}
		else {
			std::ostringstream oss; // C++ strings suck
			cout << "mesh " << pickedID << endl;
		}

		// swap window and color buffer:
		glfwSwapBuffers(display->window);
	}
}


void Gameloop::do_movement(shared_ptr<SceneObject> player)
{
	// camera controls:
	if (keys[GLFW_KEY_W])
		//this->camera.processKeyboard(FORWARD, deltaTime);
		player->translate(glm::vec3(5.0f*deltaTime, 0.0f, 0.0f));
	if (keys[GLFW_KEY_S])
		//this->camera.processKeyboard(BACKWARD, deltaTime);
		player->translate(glm::vec3(-5.0f*deltaTime, 0.0f, 0.0f));
	if (keys[GLFW_KEY_A])
		//this->camera.processKeyboard(LEFT, deltaTime);
		player->translate(glm::vec3(0.0f, 0.0f, -5.0f*deltaTime));
	if (keys[GLFW_KEY_D])
		//this->camera.processKeyboard(RIGHT, deltaTime);
		player->translate(glm::vec3(0.0f, 0.0f, 5.0f*deltaTime));
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