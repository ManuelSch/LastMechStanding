#include "Bullet.h"



Bullet::Bullet(SceneObject* parent, shared_ptr<Player> player)
{
	cout << "Bullet()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/bullet.vert", "Resources/Shaders/bullet_enemy.frag");
	//this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Bullet/bullet.obj");

	this->parent = parent;
	this->player = player;

	this->position = parent->position;
}


Bullet::~Bullet()
{
}

void Bullet::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	if (this->collide) {
		// move bullet:
		GLfloat velocity = this->movementSpeed * deltaTime;
		this->position += direction * velocity;
		
		if (distance(this->position, player->position) < 1.0f) {
			player->decreaseHealthPoints(4.0f);
			collide = false;
			visible = false;
		}

		for (GLuint i = 0; i < sceneObjects->size(); i++) {
			if ((*sceneObjects)[i]->objectID != this->objectID) {
				if (this->intersectsWith((*sceneObjects)[i])) {
					collide = false;
					visible = false;
					break;
				}
			}
		}
	}

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->update(deltaTime, sceneObjects);
	}
}

void Bullet::onClick()
{
}

void Bullet::shoot(glm::vec3 shootTowards, glm::vec3 offsetPosition)
{
	this->position = parent->position;

	shootTowards.x += (GLfloat)((double)rand() / (double)RAND_MAX) * 1.0f - 0.5f;
	shootTowards.y += (GLfloat)((double)rand() / (double)RAND_MAX) * 1.0f - 0.5f;
	shootTowards.z += (GLfloat)((double)rand() / (double)RAND_MAX) * 1.0f - 0.5f;

	this->direction = glm::normalize(shootTowards - (this->position + offsetPosition));
	this->position += offsetPosition;
	this->collide = true;
	this->visible = true;
}
