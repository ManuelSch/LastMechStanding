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
	shared_ptr<SceneObject> floor;


	//floor:
	floor = make_shared<Floor>();
	floor->translate(glm::vec3(0.0f, -2.0f, 0.0f));
	floor->scale(glm::vec3(6.0f, 0.01f, 3.0f));
	sceneObjects.push_back(floor);

	// first cube:
	player = make_shared<Character>();
	player->translate(glm::vec3(0.0f, -1.75f, 0.0f));
	player->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	sceneObjects.push_back(player);

	enemy = make_shared<Enemy>();
	enemy->translate(glm::vec3(2.0f, -1.75f, 0.0f));
	enemy->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	enemy->rotate(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	sceneObjects.push_back(enemy);

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
		do_movement(player, enemy);

		/*
		* Update objects:
		*/
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->update(deltaTime);
			}
		}


		// transformation matrices:
		glm::mat4 projection = glm::perspective(camera.zoom, (float)display->width / (float)display->height, 0.1f, 100.0f);
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
		int pickedID =
			data[0] +
			data[1] * 256 +
			data[2] * 256 * 256;
		if (pickedID == 16777215) {
			cout << "background" << endl;
		}
		else {
			std::ostringstream oss; // C++ strings suck
			cout << "mesh " << pickedID << endl;
		}
		
		/*
		* Draw objects:
		*/
		// clear color and depth buffers:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->draw(&view, &projection, &camera, &lightSources);
			}
		}		

		//should draw HUD, doesn't work
		drawHUD();


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
	//pas in 2D Ortho screen coordinates
	glOrtho(0, display->width, display->height, 0, -1, 1);
	//switch to model view
	glMatrixMode(GL_MODELVIEW);
	//initialize current model view matrix
	glLoadIdentity();

	//disabel depth-testing
	glDisable(GL_DEPTH_TEST);


	glColor3ub(240, 240, 240);//white
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


void Gameloop::do_movement(shared_ptr<SceneObject> player, shared_ptr<SceneObject> enemy)
{
	// player controls:
	if (keys[GLFW_KEY_W])
		player->move(Player::FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		player->move(Player::BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		player->move(Player::LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		player->move(Player::RIGHT, deltaTime);
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



