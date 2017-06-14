#include "Bullet.h"



Bullet::Bullet(SceneObject* parent)
{
	cout << "Bullet()" << endl;
	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	//this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Bullet/bullet.obj");

	this->parent = parent;

	this->position = parent->position;
}


Bullet::~Bullet()
{
}

void Bullet::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	if (this->collide) {
		// move bullet:
		GLfloat velocity = this->movementSpeed * deltaTime;/*
		glm::vec3 translation1 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 translation2 = glm::vec3(1.0f, 0.0f, 0.0f);
		translation1 = glm::normalize(glm::rotate(translation1, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f)));
		translation2 = glm::normalize(glm::rotate(translation2, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, -1.0f)));
		glm::vec3 translation = glm::vec3(0.0f);
		translation.x = (abs(translation1.x) > abs(translation2.x) ? translation1.x : translation2.x);
		translation.y = (abs(translation1.y) > abs(translation2.y) ? translation1.y : translation2.y);
		translation.z = (abs(translation1.z) > abs(translation2.z) ? translation1.z : translation2.z);
		translation.x = translation1.x;
		translation.z = translation1.z;
		this->position += translation;*/

		/*if (asdf) {
		printf("%3.2f, %3.2f, %3.2f\n", translation1.x, translation1.y, translation1.z);
		printf("%3.2f, %3.2f, %3.2f\n", translation2.x, translation2.y, translation2.z);
		asdf = false;
		}
		*/
		this->position += direction * velocity;
	}

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->update(deltaTime, sceneObjects);
	}
}

void Bullet::onClick()
{
}

void Bullet::shoot(glm::vec3 shootTowards)
{
	this->position = parent->position;
	/*this->angle = glm::vec3(
		0.0f,
		calculateAngle(this->position.x, this->position.z, shootTowards.x, shootTowards.z),
		calculateAngle(this->position.x, this->position.y, shootTowards.x, shootTowards.y));*/

	this->direction = glm::normalize(shootTowards - this->position);
	this->collide = true;
	this->visible = true;
}
