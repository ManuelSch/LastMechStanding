#include "Gameloop.h"



Gameloop::Gameloop(Display* _display) : display(_display), camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
	// initialize member variables:
	for (GLuint i = 0; i < 1024; i++) {
		keys[i] = false;
	}
	for (GLuint i = 0; i < 8; i++) {
		mouseButtons[i] = false;
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
	// create GUI:
	shared_ptr<GUI> gui = make_shared<GUI>();

	// create player and enemy objects:
	shared_ptr<Enemy> enemy;
	shared_ptr<Arena> arena;

	player = make_shared<Player>(&camera, gui);
	sceneObjects.push_back(player);

	arena = make_shared<Arena>();
	sceneObjects.push_back(arena);

	enemy = make_shared<Enemy>();
	enemy->translate(glm::vec3(2.0f, 0.0f, 0.0f));
	sceneObjects.push_back(enemy);

	/*
	enemy = make_shared<Enemy>();
	enemy->translate(glm::vec3(5.0f, -1.75f, 0.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);

	enemy = make_shared<Enemy>();
	enemy->translate(glm::vec3(5.0f, -1.75f, 3.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);

	enemy = make_shared<Enemy>();
	enemy->translate(glm::vec3(-5.0f, -1.75f, 3.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);
	*/

	// create sunlight:
	shared_ptr<LightSource> sunLight = make_shared<LightSource>(LightSource::DIRECTIONAL);
	sunLight->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	sunLight->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	sunLight->diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	sunLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	lightSources.push_back(sunLight);

	
	// projection matrix:
	glm::mat4 projection = glm::perspective(45.0f, (float)display->width / (float)display->height, 0.1f, 100.0f);


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
		processKeyboardInput();

		// transformation matrices:
		glm::mat4 view = camera.getViewMatrix();

		/*
		* Draw picking colors:
		*/
		// clear color and depth buffers:
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->drawPicking(&view, &projection, &camera, i);
			}
		}

		glFlush();
		glFinish();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		unsigned char data[4];
		glReadPixels(display->width / 2, display->height / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
		int pickedID = data[0] + data[1] * 256 + data[2] * 256 * 256;
		if (pickedID == 16777215) {
			cout << "background" << endl;
		}
		else {
			cout << "mesh " << pickedID << endl;
			processMouseButtonInput(sceneObjects[pickedID]);
		}




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
		// clear color and depth buffers:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->draw(&view, &projection, &camera, &lightSources);
			}
		}

		//should draw HUD, doesn't work
		drawHUD();

		gui->healthBar->draw();

		// swap window and color buffer:
		glfwSwapBuffers(display->window);
	}
}


void Gameloop::drawHUD() {

	//switch to projection matrix
	glMatrixMode(GL_PROJECTION);
	//push on new Matrix
	glPushMatrix();
	//reset current matrix
	glLoadIdentity();
	//pass in 2D Ortho screen coordinates
	glOrtho(0, display->width, display->height, 0, -1, 10);
	//switch to model view
	glMatrixMode(GL_MODELVIEW);
	//initialize current model view matrix
	glLoadIdentity();

	//disable depth testing
	glDisable(GL_DEPTH_TEST);

	glColor3f(1.0, 1.0, 1.0); //white
	glLineWidth(2.0);
	glBegin(GL_LINES);
	//horizontal line
	glVertex2i(display->width / 2 - 7, display->height / 2);
	glVertex2i(display->width / 2 + 7, display->height / 2);
	glEnd();
	//vertical line
	glBegin(GL_LINES);
	glVertex2i(display->width / 2, display->height / 2 + 7);
	glVertex2i(display->width / 2, display->height / 2 - 7);
	glEnd();

	//Enable depth-testing
	glEnable(GL_DEPTH_TEST);

	//enter into projection matrix mode
	glMatrixMode(GL_PROJECTION);

	//pop off last matrix
	glPopMatrix();

	//back to model view matrix in 3D
	glMatrixMode(GL_MODELVIEW);

}

void Gameloop::drawHUDelements() {
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(15, 0, 0);
	glEnd(); // Render now
}


void Gameloop::processKeyboardInput()
{
	// player controls:
	if (keys[GLFW_KEY_W]) {
		player->movePosition(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S]) {
		player->movePosition(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		player->movePosition(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D]) {
		player->movePosition(RIGHT, deltaTime);
	}
}

void Gameloop::processMouseButtonInput(shared_ptr<SceneObject> pickedObject)
{
	if (mouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		pickedObject->onClick();
		mouseButtons[GLFW_MOUSE_BUTTON_LEFT] = false;
	}
}

void Gameloop::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
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

void Gameloop::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{

	if (button >= 0 && button < 8)
	{
		if (action == GLFW_PRESS)
			mouseButtons[button] = true;
		else if (action == GLFW_RELEASE)
			mouseButtons[button] = false;
	}

	// For testing purposes (decreases the players health points):
	if (mouseButtons[GLFW_MOUSE_BUTTON_RIGHT]) {
		player->decreaseHealthPoints(20.0f);
		mouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = false;
	}
}

void Gameloop::mouseCallback(GLFWwindow* window, double xpos, double ypos)
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

	this->player->moveView(xoffset, yoffset);
}
