#include "Enemy.h"

Enemy::Enemy(shared_ptr<GUI> gui) : gui(gui)
{

	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_unique<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->model = Model("Resources/Models/CubeEnemy/cubeEnemy.dae");

	movementSpeed = MOVEMENT_SPEED;
	healthPoints = HEALTH_POINTS_MAX;

	setNewDestination();
}

Enemy::~Enemy()
{
}

void Enemy::update(GLfloat deltaTime)
{
	GLfloat size = this->healthPoints / 100.0f;
	size = max(size, 0.0f);
	this->scaling = glm::vec3(1.0f) * size;

	if (distance(position, destination) < 1.0f) {
		setNewDestination();
	}
	else {
		this->moveTowards(this->destination, movementSpeed * deltaTime);
	}
}

void Enemy::onClick()
{
	this->healthPoints -= 25;

	this->gui->enemyHealthBar->setHealthPointsInPercent(healthPoints / HEALTH_POINTS_MAX);
}


void Enemy::setNewDestination()
{
	destination.x = -20 + rand() / double(RAND_MAX) * 40;
	destination.z = -20 + rand() / double(RAND_MAX) * 40;
}