#include "Player.h"

Player::Player(Camera* camera, shared_ptr<GUI> gui, GLfloat displayRatio) : camera(camera), gui(gui)
{
	cout << "Player() = " << objectID << endl;
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
	this->model.boundingBox->minVertexPos.y -= 1.75f * (1 / this->scaling.y);

	camera->updateCameraVectors(position, angle);
	
	for (GLuint i = 0; i < 15; i++) {
		shared_ptr<BulletPlayer> bullet = make_shared<BulletPlayer>(this);
		bullet->collide = false;
		bullet->visible = false;
		this->children.push_back(bullet);
		this->bullets.push_back(bullet);
	}
}

Player::~Player()
{
}

void Player::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	// gravity:
	this->translate(glm::vec3(0.0f, -deltaTime * GRAVITY, 0.0f), sceneObjects);

	// jumping:
	if (this->isJumping) {
		glm::vec3 jumpDest = glm::vec3(position.x, position.y + jumpHeight, position.z);
		this->movePosition(UP, deltaTime * distance(this->position, jumpDest) * JUMP_SPEED, sceneObjects);

		if (distance(this->position, jumpDest) < 0.1f || this->position.y > jumpDest.y) {
			this->isJumping = false;
		}
		jumpHeight -= deltaTime * GRAVITY*0.3f;
	}

	camera->updateCameraVectors(position, angle);



	for (GLuint i = 0; i < bullets.size(); i++) {
		if (distance(position, bullets[i]->position) > 200.0f) {
			bullets[i]->collide = false;
			bullets[i]->visible = false;
		}
	}
	
	shootTimer = min(10.0f, shootTimer+deltaTime);

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->update(deltaTime, sceneObjects);
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
		this->translate(glm::vec3(0.0f, deltaTime, 0.0f), sceneObjects);
		break;
	case DOWN:
		this->translate(glm::vec3(0.0f, -deltaTime, 0.0f), sceneObjects);
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
	
	// constraint so player can't look further up or down than 90°:
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

void Player::shoot()
{
	if (shootTimer > 0.1f) {
		shootTimer = 0.0f;
		shootLeft = !shootLeft;

		for (GLuint i = 0; i < bullets.size(); i++) {
			if (!bullets[i]->collide && !bullets[i]->visible) {
				bullets[i]->shoot(camera->position + camera->front, (shootLeft ? camera->right : glm::vec3(-1.0f, -1.0f, -1.0f) * camera->right));
				this->gui->crossHair->spread();
				break;
			}
		}
	}
}


