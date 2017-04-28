#include "Enemy.h"

Enemy::Enemy()
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_unique<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->model = Model("Resources/Models/CubeEnemy/cubeEnemy.dae");

	this->healthPoints = 100.0f;
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
	GLfloat size = this->healthPoints / 100.0f;
	size = max(size, 0.0f);
	this->scaling = glm::vec3(1.0f) * size;
}

void Enemy::onClick()
{
	this->healthPoints -= 25;
}
