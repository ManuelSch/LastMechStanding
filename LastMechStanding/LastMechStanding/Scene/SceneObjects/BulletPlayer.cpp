#include "BulletPlayer.h"



BulletPlayer::BulletPlayer(SceneObject* parent)
{
	cout << "BulletPlayer()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/bullet.vert", "Resources/Shaders/bullet.frag");
	//this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Bullet/bullet.obj");

	this->parent = parent;

	this->position = parent->position;
}


BulletPlayer::~BulletPlayer()
{
}

void BulletPlayer::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	if (this->collide) {
		// move bullet:
		GLfloat velocity = this->movementSpeed * deltaTime;
		this->position += direction * velocity;


		for (GLuint i = 0; i < sceneObjects->size(); i++) {
			if ((*sceneObjects)[i]->objectID != this->objectID && (*sceneObjects)[i]->objectID != this->parent->objectID) {
				if ((*sceneObjects)[i]->collide) {
					if (this->intersectsWith((*sceneObjects)[i]) || (distance(this->position, (*sceneObjects)[i]->position) < 1.0f)) {
						collide = false;
						visible = false;

						(*sceneObjects)[i]->onClick();

						break;
					}
				}
			}
		}
	}

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->update(deltaTime, sceneObjects);
	}
}

void BulletPlayer::onClick()
{
}

void BulletPlayer::shoot(glm::vec3 shootTowards, glm::vec3 offsetPosition)
{
	this->position = parent->position;
	/*
	shootTowards.x += (GLfloat)((double)rand() / (double)RAND_MAX) * 1.0f - 0.5f;
	shootTowards.y += (GLfloat)((double)rand() / (double)RAND_MAX) * 1.0f - 0.5f;
	shootTowards.z += (GLfloat)((double)rand() / (double)RAND_MAX) * 1.0f - 0.5f;
	*/
	this->direction = glm::normalize(shootTowards - this->position);
	this->position += glm::normalize(offsetPosition) * .5f;
	this->collide = true;
	this->visible = true;
}
