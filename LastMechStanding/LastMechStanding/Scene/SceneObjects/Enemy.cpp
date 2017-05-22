#include "Enemy.h"

Enemy::Enemy(shared_ptr<GUI> gui) : gui(gui)
{

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->model = Model("Resources/Models/CubeEnemy/cubeEnemy.dae");

	Enemy::minBBspawn = this->model.minBB;
	Enemy::maxBBspawn = this->model.maxBB;

	Enemy::minBB = glm::vec3(this->getModelMatrix() * glm::vec4(minBBspawn, 1));
	Enemy::maxBB = glm::vec3(this->getModelMatrix() * glm::vec4(maxBBspawn, 1));

	movementSpeed = MOVEMENT_SPEED;
	healthPoints = HEALTH_POINTS_MAX;

	setNewDestination();
}

Enemy::~Enemy()
{
}

void Enemy::update(GLfloat deltaTime)
{
	if (this->healthPoints <= 0) {
		this->dead = true;
	}

	if (distance(glm::vec2(position.x, position.z), glm::vec2(destination.x, destination.z)) < 1.0f) {
		setNewDestination();
	}
	else {
		this->moveTowards(this->destination, movementSpeed * deltaTime);
	}

	minBB = glm::vec3(this->getModelMatrix() * glm::vec4(minBBspawn, 1));
	maxBB = glm::vec3(this->getModelMatrix() * glm::vec4(maxBBspawn, 1));
}

void Enemy::onClick()
{
	this->healthPoints -= 25;

	this->gui->enemyHealthBar->setHealthPointsInPercent(healthPoints / HEALTH_POINTS_MAX);
}


void Enemy::setNewDestination()
{
	destination.x = -40 + rand() / double(RAND_MAX) * 80;
	destination.y = position.y;
	destination.z = -40 + rand() / double(RAND_MAX) * 80;
}

bool Enemy::collidesWithEnemy(Enemy* enemy) 
{
	if (!((minBB.x < enemy->minBB.x && maxBB.x < enemy->minBB.x) || (minBB.x > enemy->maxBB.x && maxBB.x > enemy->maxBB.x)) &&
		!((minBB.y < enemy->minBB.y && maxBB.y < enemy->minBB.y) || (minBB.y > enemy->maxBB.y && maxBB.y > enemy->maxBB.y)) &&
		!((minBB.z > enemy->minBB.z && maxBB.z > enemy->minBB.z) || (minBB.z < enemy->maxBB.z && maxBB.z < enemy->maxBB.z))) {
		return true;
	}
	return false;
}
