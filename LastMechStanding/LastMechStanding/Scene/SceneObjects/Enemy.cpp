#include "Enemy.h"

Enemy::Enemy(shared_ptr<GUI> gui, shared_ptr<Player> player) : gui(gui), player(player)
{
	cout << "Enemy()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Mech/mechbottom.obj");

	movementSpeed = MOVEMENT_SPEED;
	healthPoints = HEALTH_POINTS_MAX;

	this->lastPosition = position;
	this->timeStandingStill = 0.0f;

	this->children.push_back(make_shared<EnemyTop>(this, player));

	setNewDestination();
}

Enemy::~Enemy()
{
}

void Enemy::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	if (!this->visible) {
		return;
	}

	//printf("%3.2f, %3.2f, %3.2f\n", position.x, position.y, position.z);

	if (position.x > 45.0f) {
		position.x = 45.0f;
		this->setNewDestination();
	}
	if (position.x < -45.0f) {
		position.x = -45.0f;
		this->setNewDestination();
	}
	if (position.y > 45.0f) {
		position.y = 45.0f;
		this->setNewDestination();
	}
	if (position.y < -45.0f) {
		position.y = -45.0f;
		this->setNewDestination();
	}

	// gravity:
	this->translate(glm::vec3(0.0f, -deltaTime * GRAVITY, 0.0f), sceneObjects);
	if ((GLfloat)((double)rand() / (double)RAND_MAX) > 0.95) {
		this->translate(glm::vec3(0.0f, -deltaTime * GRAVITY / 10.f, 0.0f), sceneObjects);
	}


	if (this->healthPoints <= 0) {
		this->visible = false;
		this->collide = false;
		this->gui->scoreScreen->defeatedEnemies++;
		for (GLuint i = 0; i < children.size(); i++) {
			this->children[i]->visible = false;
			this->children[i]->collide = false;
		}
	}

	if (distance(glm::vec2(position.x, position.z), glm::vec2(destination.x, destination.z)) < 1.0f) {
		setNewDestination();
	}
	else {
		this->moveTowards(this->destination, movementSpeed * deltaTime, sceneObjects);
		//!--
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
			//!--
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

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->update(deltaTime, sceneObjects);
	}
}

void Enemy::onClick()
{
	this->healthPoints -= 25;

	this->gui->enemyHealthBar->setHealthPointsInPercent(healthPoints / HEALTH_POINTS_MAX);

	this->children[0]->angle.y = this->calculateAngle(position.x, position.z, player->position.x, player->position.z);
	this->destination = player->position;
}


void Enemy::reset()
{
	this->position = SceneObject::getRandomPosition(0.0f);
	this->setNewDestination();
	this->lastPosition = this->position;
	this->timeStandingStill = 0.0f;
	this->collide = true;
	this->visible = true;
	this->dead = false;

	this->healthPoints = HEALTH_POINTS_MAX;

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		children[j]->collide = true;
		children[j]->visible = true;
		children[j]->position = this->position;
		children[j]->angle = this->angle;
	}
}

void Enemy::setNewDestination()
{
	destination = SceneObject::getRandomPosition(position.y);
}