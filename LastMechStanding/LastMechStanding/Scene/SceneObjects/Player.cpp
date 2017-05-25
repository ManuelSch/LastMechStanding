#include "Player.h"

Player::Player(Camera* camera, shared_ptr<GUI> gui, GLfloat displayRatio) : camera(camera), gui(gui)
{
	cout << "Player()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	// decide which model to load depending on the display aspect ratio:
	if (displayRatio < (4.0f / 3.0f + 16.0f / 9.0f) / 2.0f) {
		this->model = Model("Resources/Models/Player/Player_4by3ratio.obj");
	}
	else {
		this->model = Model("Resources/Models/Player/Player_16by9ratio.obj");
	}

	movementSpeed = MOVEMENT_SPEED;
	mouseSensitivity = MOUSE_SENSITIVITY;
	healthPoints = HEALTH_POINTS_MAX;

	this->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	this->position = glm::vec3(0.0f, 20.0f, 0.0f);

	camera->updateCameraVectors(position, angle);
}

Player::~Player()
{
}

void Player::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	this->movePosition(DOWN, deltaTime, sceneObjects);

	if (this->isJumping) {
		glm::vec3 jumpDest = glm::vec3(position.x, position.y + jumpHeight, position.z);
		//this->moveTowards(jumpDest, deltaTime*.02f, sceneObjects);
		this->movePosition(UP, deltaTime * distance(this->position, jumpDest), sceneObjects);

		if (distance(this->position, jumpDest) < 0.5f) {
			this->isJumping = false;
		}
		jumpHeight -= deltaTime;
	}
}

void Player::movePosition(Movement direction, GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	switch (direction) {
	case FORWARD:
		this->translate(glm::rotate(glm::vec3(velocity, 0.0f, 0.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)), sceneObjects);
		break;
	case BACKWARD:
		this->translate(glm::rotate(glm::vec3(-velocity, 0.0f, 0.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)), sceneObjects);
		break;
	case LEFT:
		this->translate(glm::rotate(glm::vec3(0.0f, 0.0f, -velocity), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)), sceneObjects);
		break;
	case RIGHT:
		this->translate(glm::rotate(glm::vec3(0.0f, 0.0f, velocity), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)), sceneObjects);
		break;
	case UP:
		this->translate(glm::rotate(glm::vec3(0.0f, velocity * 4.0f, 0.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)), sceneObjects);
		break;
	case DOWN:
		this->translate(glm::rotate(glm::vec3(0.0f, -velocity * 1.5f, 0.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)), sceneObjects);
		break;
	}

	camera->updateCameraVectors(position, angle);
}

void Player::moveView(GLfloat xOffset, GLfloat yOffset)
{
	// apply mouse sensitivity:
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	this->rotate(xOffset, glm::vec3(0.0f, -1.0f, 0.0f));
	this->rotate(yOffset, glm::vec3(0.0f, 0.0f, 1.0f));
	
	// constraint so player can't look further up or down than 90�:
	if (true)
	{
		if (this->angle.z > 89.0f)
			this->angle.z = 89.0f;
		if (this->angle.z < -89.0f)
			this->angle.z = -89.0f;
	}

	camera->updateCameraVectors(position, angle);
}

void Player::decreaseHealthPoints(GLfloat damage)
{
	this->healthPoints -= damage;
	this->healthPoints = max(0.0f, healthPoints);

	this->gui->healthBar->setHealthPointsInPercent(healthPoints / HEALTH_POINTS_MAX);
}

void Player::jump()
{
	if (canJump) {
		jumpHeight = 1.2f;
		canJump = false;
		isJumping = true;
	}
}
