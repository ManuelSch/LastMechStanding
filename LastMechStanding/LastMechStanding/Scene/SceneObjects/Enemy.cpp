#include "Enemy.h"

Enemy::Enemy(shared_ptr<GUI> gui) : gui(gui)
{
	cout << "Enemy()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/CubeEnemy/cubeEnemy.dae");

	movementSpeed = MOVEMENT_SPEED;
	healthPoints = HEALTH_POINTS_MAX;

	this->lastPosition = position;
	this->timeStandingStill = 0.0f;

	setNewDestination();
}

Enemy::~Enemy()
{
}

void Enemy::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	// gravity:
	this->translate(glm::vec3(0.0f, -deltaTime * GRAVITY, 0.0f), sceneObjects);


	if (this->healthPoints <= 0) {
		this->dead = true;
	}

	if (distance(glm::vec2(position.x, position.z), glm::vec2(destination.x, destination.z)) < 1.0f) {
		setNewDestination();
	}
	else {
		this->moveTowards(this->destination, movementSpeed * deltaTime, sceneObjects);
	}


	if (distance(this->lastPosition, this->position) > 0.05f) {
		this->timeStandingStill = 0;
	}
	else {
		this->timeStandingStill += deltaTime;
	}
	this->lastPosition = position;

	if (timeStandingStill > 1.0f) {
		if ((GLfloat)((double)rand() / (double)RAND_MAX) > 0.5) {
			this->jump();
		}
		else {
			setNewDestination();
		}
		this->timeStandingStill = 0;
	}



	// jumping:
	if (this->isJumping) {
		glm::vec3 jumpDest = glm::vec3(position.x, position.y + jumpHeight, position.z);
		this->translate(glm::vec3(0.0f, deltaTime * distance(this->position, jumpDest) * JUMP_SPEED, 0.0f), sceneObjects);

		if (distance(this->position, jumpDest) < 0.1f) {
			this->isJumping = false;
		}
		jumpHeight -= deltaTime * GRAVITY*0.3f;
	}

}

void Enemy::onClick()
{
	this->healthPoints -= 25;

	this->gui->enemyHealthBar->setHealthPointsInPercent(healthPoints / HEALTH_POINTS_MAX);
}


void Enemy::setNewDestination()
{
	destination = SceneObject::getRandomPosition(position.y);
}