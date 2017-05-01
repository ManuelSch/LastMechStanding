#include "Player.h"

Player::Player(Camera* camera, shared_ptr<GUI> gui) : camera(camera), gui(gui)
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_unique<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->model = Model("Resources/Models/Player/Player.obj");

	movementSpeed = MOVEMENT_SPEED;
	mouseSensitivity = MOUSE_SENSITIVITY;
	healthPoints = HEALTH_POINTS_MAX;

	this->scale(glm::vec3(0.2f, 0.2f, 0.2f));

	camera->updateCameraVectors(position, angle);
}

Player::~Player()
{
}

void Player::update(GLfloat deltaTime)
{
}

void Player::movePosition(Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	switch (direction) {
	case FORWARD:
		this->translate(glm::rotate(glm::vec3(velocity, 0.0f, 0.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case BACKWARD:
		this->translate(glm::rotate(glm::vec3(-velocity, 0.0f, 0.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case LEFT:
		this->translate(glm::rotate(glm::vec3(0.0f, 0.0f, -velocity), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)));
		break;
	case RIGHT:
		this->translate(glm::rotate(glm::vec3(0.0f, 0.0f, velocity), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)));
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

	this->gui->healthBar->setHealthPointsInPercent(healthPoints / HEALTH_POINTS_MAX);
}
