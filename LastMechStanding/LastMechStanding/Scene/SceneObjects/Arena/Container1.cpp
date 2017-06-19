#include "Container1.h"



Container1::Container1(glm::vec3 position)
{
	cout << "Container1()" << endl;

	this->position = position;

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	if ((GLfloat)((double)rand() / (double)RAND_MAX) >= 0.5) {
		this->model = Model("Resources/Models/Container/container.obj");
	}
	else {
		this->model = Model("Resources/Models/Container/container2.obj");
	}

	this->scale(glm::vec3(((GLfloat)((double)rand() / (double)RAND_MAX) * 6.0f + 1.0f), ((GLfloat)((double)rand() / (double)RAND_MAX) * 2.0f + 1.0f), ((GLfloat)((double)rand() / (double)RAND_MAX) * 12.0f + 1.0f)));

	this->position.y = GROUND_LEVEL_Y;

	this->model.boundingBox->getAllPositions(&(this->position), &(this->scaling), &(this->position), nullptr, 0.0f);
	this->model.boundingBox->getAllPositions(&(this->position), &(this->scaling), &glm::vec3(1234.0f, 1234.0f, 1234.0f), nullptr, 0.0f);
}


Container1::~Container1()
{
}

void Container1::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
}
