#include "Gameloop.h"



Gameloop::Gameloop(shared_ptr<Display> _display, shared_ptr<Font> _font) : display(_display), font(_font), camera(glm::vec3(0.0f, 0.0f, 3.0f))
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

	// enable blending (alpha transparency):
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// create short keys controller (F1-F9, Esc)
	this->shortKeys = make_shared<ShortKeys>(display->window);

	// initialize framebuffer:
	/*
	this->framebuffer = make_shared<Framebuffer>(display);
	*/
}


Gameloop::~Gameloop()
{
}


void Gameloop::run()
{
	// create GUI:
	this->gui = make_shared<GUI>(display->getDisplayRatio(), this->shortKeys, this->font);

	// create player and enemy objects:
	shared_ptr<Enemy> enemy;
	shared_ptr<Arena> arena;

	player = make_shared<Player>(&camera, gui, display->getDisplayRatio());
	sceneObjects.push_back(player);

	arena = make_shared<Arena>();
	sceneObjects.push_back(arena);

	for (GLuint i = 0; i < 1; i++) {
		enemy = make_shared<Enemy>(gui);
		enemy->translate(glm::vec3(0.0f, 0.0f, 3.0f), &sceneObjects);
		sceneObjects.push_back(enemy);
	}


	// create sunlight:
	shared_ptr<LightSource> sunLight = make_shared<LightSource>(LightSource::DIRECTIONAL);
	sunLight->direction = glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f));
	sunLight->ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	sunLight->diffuse = glm::vec3(0.9f, 0.9f, 0.7f);
	sunLight->specular = glm::vec3(0.7f, 0.7f, 0.7f);
	//sunLight->position = glm::vec3(-2.0f, 4.0f, -1.0f);		// for the shadow map
	sunLight->position = player->position;
	lightSources.push_back(sunLight);

	// create lamps (for testing purposes):
	/*
	shared_ptr<Lamp> lamp = make_shared<Lamp>();
	lamp->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	lamp->position = sunLight->position;
	sceneObjects.push_back(lamp);

	shared_ptr<Lamp> sceneCenter = make_shared<Lamp>();
	sceneCenter->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	sceneCenter->position = sunLight->position + sunLight->direction;
	sceneObjects.push_back(sceneCenter);
	*/

	// initialize shadow map:
	this->shadowMap = make_shared<ShadowMap>(sunLight);

	
	// projection matrix:
	glm::mat4 projection = glm::perspective(45.0f, display->getDisplayRatio(), 0.1f, 100.0f);

	

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
		processKeyboardInput(&sceneObjects);

		// view matrix:
		glm::mat4 view = camera.getViewMatrix();


		/*
		* Bind to framebuffer and draw to color texture:
		*//*
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		*/


		/*
		* Delete dead objects:
		*/
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr && sceneObjects[i]->dead == true) {
				sceneObjects.erase(sceneObjects.begin() + i);
			}
		}


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
			//cout << "background" << endl;
		}
		else {
			//cout << "mesh " << pickedID << endl;
			processMouseButtonInput(sceneObjects[pickedID]);
		}


		/*
		* Update objects:
		*/
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->update(deltaTime, &sceneObjects);
			}
		}


		/*
		* render to depth map:
		*/
		if (this->shortKeys->shadowMappinOn) {
			sunLight->position = player->position;
			shadowMap->renderToDepthMap(&sceneObjects);
		}


		/*
		* render scene as normal with shadow mapping (using depth map):
		*/
		glViewport(0, 0, display->width, display->height);
		// clear color and depth buffers:
		glClearColor(0.45f, 0.78f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		// draw objects:
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				if (this->shortKeys->shadowMappinOn) {
					sceneObjects[i]->draw(&view, &projection, &camera, &lightSources, &(shadowMap->lightSpaceMatrix), &(shadowMap->depthMap));
				}
				else {
					sceneObjects[i]->draw(&view, &projection, &camera, &lightSources, nullptr, nullptr);
				}
			}
		}
		

		/*
		* Draw and update GUI:
		*/
		this->gui->update(deltaTime);
		this->gui->draw();

		/*
		* Bind to default framebuffer and draw the quad to the screen:
		*//*
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		framebuffer->draw();
		*/

		// swap window and frame buffer:
		glfwSwapBuffers(display->window);
	}
}


void Gameloop::processKeyboardInput(vector<shared_ptr<SceneObject>>* sceneObjects)
{
	// player controls:
	if (keys[GLFW_KEY_W]) {
		player->movePosition(FORWARD, deltaTime, sceneObjects);
	}
	if (keys[GLFW_KEY_S]) {
		player->movePosition(BACKWARD, deltaTime, sceneObjects);
	}
	if (keys[GLFW_KEY_A]) {
		player->movePosition(LEFT, deltaTime, sceneObjects);
	}
	if (keys[GLFW_KEY_D]) {
		player->movePosition(RIGHT, deltaTime, sceneObjects);
	}
	if (keys[GLFW_KEY_SPACE]) {
		player->jump();
	}
	else {
		player->jumpHeight /= 1.1f;
	}
}

void Gameloop::processMouseButtonInput(shared_ptr<SceneObject> pickedObject)
{
	if (mouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		pickedObject->onClick();
		mouseButtons[GLFW_MOUSE_BUTTON_LEFT] = false;
		this->gui->crossHair->spread();
	}
}

void Gameloop::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// check if any shortkeys (F1-F9, Esc) have been pressed:
	if (action == GLFW_PRESS) {
		this->shortKeys->pressShortKey(key);
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
