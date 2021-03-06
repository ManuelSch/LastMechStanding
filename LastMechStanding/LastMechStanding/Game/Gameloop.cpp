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


	srand(time(NULL));

	// initialize framebuffer:
	this->framebuffer = make_shared<Framebuffer>(display);
}


Gameloop::~Gameloop()
{
}


void Gameloop::run()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	shared_ptr<LoadingScreen> loadingScreen = make_shared<LoadingScreen>(font);
	loadingScreen->draw(0, display);



	// create GUI:
	this->gui = make_shared<GUI>(display->getDisplayRatio(), this->shortKeys, this->font);

	loadingScreen->draw(5, display);

	// arena:
	shared_ptr<SceneObject> arena;
	arena = make_shared<Arena>();
	sceneObjects.push_back(arena);

	loadingScreen->draw(10, display);

	// arena walls:
	sceneObjects.push_back(make_shared<ArenaWall>(glm::vec3(0.0f, 0.0f, 49.0f)));
	sceneObjects.push_back(make_shared<ArenaWall>(glm::vec3(0.0f, 0.0f, -49.0f)));
	sceneObjects.push_back(make_shared<ArenaWall>(glm::vec3(49.0f, 0.0f, 0.0f), true));
	sceneObjects.push_back(make_shared<ArenaWall>(glm::vec3(-49.0f, 0.0f, 0.0f), true));

	loadingScreen->draw(20, display);

	// arena containers:
	const GLuint numberOfContainers = 20;
	for (GLuint i = 0; i < numberOfContainers; i++) {
		glm::vec3 newPosition = glm::vec3(0.0f);
		newPosition.x = ((GLfloat)i / (GLfloat)numberOfContainers) * 90.f - 45.0f;
		newPosition.z = (GLfloat)((double)rand() / (double)RAND_MAX) * 90.0f - 45.0f;
		sceneObjects.push_back(make_shared<Container1>(newPosition));
	}

	loadingScreen->draw(30, display);




	// create player and enemy objects:
	player = make_shared<Player>(&camera, gui, display->getDisplayRatio());
	player->position.x = 46.5f;
	player->position.z = -46.5f;
	player->angle.y = 225;
	sceneObjects.push_back(player);

	loadingScreen->draw(45, display);

	vector<shared_ptr<Enemy>> enemies;
	shared_ptr<Enemy> enemy;
	const GLuint numberOfEnemies = 3;
	for (GLuint i = 0; i < numberOfEnemies; i++) {
		enemy = make_shared<Enemy>(gui, player);
		sceneObjects.push_back(enemy);
		enemies.push_back(enemy);
		do {
			enemy->position = SceneObject::getRandomPosition(0.0f);
		} while (distance(enemy->position, player->position) < 40.0f);
		enemy->visible = false;
		enemy->collide = false;

		loadingScreen->draw(60 + i * 15, display);
	}



	// create sunlight:
	shared_ptr<LightSource> sunLight = make_shared<LightSource>(LightSource::DIRECTIONAL);
	sunLight->direction = glm::normalize(glm::vec3(-0.25f, -1.0f, -0.35f));
	sunLight->ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	sunLight->diffuse = glm::vec3(0.9f, 0.9f, 0.7f);
	sunLight->specular = glm::vec3(0.7f, 0.7f, 0.7f);
	//sunLight->position = glm::vec3(-2.0f, 4.0f, -1.0f);		// for the shadow map
	sunLight->position = player->position;
	lightSources.push_back(sunLight);

	loadingScreen->draw(90, display);

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

	loadingScreen->draw(95, display);
	
	// projection matrix:
	glm::mat4 projection = glm::perspective(45.0f, display->getDisplayRatio(), 0.1f, 145.0f);

	

	// frame independency:
	deltaTime = 0.0f;
	lastFrame = glfwGetTime() - 1/30.0f;

	GLfloat enemySpawnTime = 5.0f;
	GLfloat enemySpawnInterval = 10.0f;


	// game loop:
	while (!glfwWindowShouldClose(display->window) && player->healthPoints > 0.0f)
	{
		// calculate delta time for frame independency:
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//deltaTime = max(deltaTime, 0.01f);

		// check if any events were triggered:
		glfwPollEvents();
		processKeyboardInput(&sceneObjects);


		/*
		* Bind to framebuffer and draw to color texture:
		*/
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glEnable(GL_DEPTH_TEST);


		enemySpawnTime += deltaTime;
		if (enemySpawnTime > enemySpawnInterval) {
			enemySpawnTime = 0.0f;
			enemySpawnInterval *= 0.98f;
			for (GLuint i = 0; i < enemies.size(); i++) {
				if (!enemies[i]->collide && !enemies[i]->visible) {
					enemies[i]->reset((100.0f / enemySpawnInterval) * (100.0f / (enemySpawnInterval*0.95f)));
					break;
				}
			}
		}
		
		processMouseButtonInput();


		/*
		* Update objects:
		*/
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				sceneObjects[i]->update(deltaTime, &sceneObjects);
			}
		}


		// view matrix:
		glm::mat4 view = camera.getViewMatrix();


		/*
		* render to depth map:
		*/
		if (this->shortKeys->shadowMappinOn) {
			sunLight->position = player->position;
			shadowMap->renderToDepthMap(&sceneObjects, shortKeys.get());
		}
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);


		glPolygonMode(GL_FRONT_AND_BACK, (shortKeys->wireFrameOn ? GL_LINE : GL_FILL));

		/*
		* render scene as normal with shadow mapping (using depth map):
		*/
		glViewport(0, 0, display->width, display->height);
		// clear color and depth buffers:
		glClearColor(BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		GLuint numberOfDrawnObjects = 0;
		// draw objects:
		for (GLuint i = 0; i < sceneObjects.size(); i++) {
			if (sceneObjects[i] != nullptr) {
				if (!shortKeys->viewFrustumCullingOn || sceneObjects[i]->objectID == player->objectID || sceneObjects[i]->isInFrustum(&(projection * view), &camera, player.get())) {
					numberOfDrawnObjects++;
					if (this->shortKeys->shadowMappinOn) {
						sceneObjects[i]->draw(&view, &projection, &camera, &lightSources, shortKeys.get(), &(shadowMap->lightSpaceMatrix), &(shadowMap->depthMap));
					}
					else {
						sceneObjects[i]->draw(&view, &projection, &camera, &lightSources, shortKeys.get(), nullptr, nullptr);
					}
				}
			}
		}
		if (shortKeys->viewFrustumCullingOn) {
			gui->viewFrustumCullingScreen->drawnElements = numberOfDrawnObjects;
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/*
		* Draw and update GUI:
		*/
		this->gui->update(deltaTime);
		this->gui->draw();


		/*
		* Bind to default framebuffer and draw the quad to the screen:
		*/
		framebuffer->draw(this->shortKeys);



		// swap window and frame buffer:
		glfwSwapBuffers(display->window);


		//cout << distance(enemy->position, player->position) << endl;
		//player->printPosition();
	}

	


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*
	* Bind to framebuffer and draw to color texture:
	*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	shared_ptr<GameoverScreen> gameoverScreen = make_shared<GameoverScreen>(font);
	gameoverScreen->draw(gui->scoreScreen->defeatedEnemies);

	// swap window and frame buffer:
	glfwSwapBuffers(display->window);

	while (!glfwWindowShouldClose(display->window))
	{
		// check if any events were triggered:
		glfwPollEvents();
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

void Gameloop::processMouseButtonInput()
{
	if (mouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		//mouseButtons[GLFW_MOUSE_BUTTON_LEFT] = false;
		this->player->shoot();
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
