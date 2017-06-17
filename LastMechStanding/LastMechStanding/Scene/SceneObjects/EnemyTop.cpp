#include "EnemyTop.h"



EnemyTop::EnemyTop(SceneObject* parent, shared_ptr<Player> player)
{
	cout << "EnemyTop()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Mech/mechTop.obj");

	this->parent = parent;
	this->player = player;

	this->position = parent->position;
	this->angle = parent->angle;
	//!--
	for (GLuint i = 0; i < 15; i++) {
		shared_ptr<Bullet> bullet = make_shared<Bullet>(this, player);
		bullet->collide = false;
		bullet->visible = false;
		this->children.push_back(bullet);
		this->bullets.push_back(bullet);
	}
}

EnemyTop::~EnemyTop()
{
}

void EnemyTop::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	this->position = parent->position;

	for (GLuint i = 0; i < bullets.size(); i++) {
		if (distance(position, bullets[i]->position) > 150.0f) {
			bullets[i]->collide = false;
			bullets[i]->visible = false;
		}
	}

	GLfloat angleToPlayer = this->calculateAngle(position.x, position.z, player->position.x, player->position.z);
	if (abs(this->angle.y - angleToPlayer) < 45 && distance(this->position, player->position) < 50.0f) {
		//cout << "see!!" << endl;
		this->angle.y = angleToPlayer;
		this->parent->destination = player->position;

		shootTimer += deltaTime;
		if (shootTimer > 0.2f) {
			shootTimer = 0.0f;

			for (GLuint i = 0; i < bullets.size(); i++) {
				if (!bullets[i]->collide && !bullets[i]->visible) {
					shootLeft = !shootLeft;
					glm::vec3 offsetPosition = glm::rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(angle.y + (shootLeft ? -90.0f : 90.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
					bullets[i]->shoot(player->position, offsetPosition);
					break;
				}
			}
		}
	}
	else {
		this->angle.y = this->parent->angle.y;
	}
	

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->update(deltaTime, sceneObjects);
	}
}

void EnemyTop::onClick()
{
	this->parent->onClick();
}
