#include "Arena.h"


Arena::Arena()
{
	cout << "Arena()" << endl;

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Arena/arena.obj");

	this->position.y = GROUND_LEVEL_Y;

	this->model.boundingBox->getAllPositions(&(this->position), &(this->scaling), &(this->position), nullptr, 0.0f);
	this->model.boundingBox->getAllPositions(&(this->position), &(this->scaling), &glm::vec3(1234.0f, 1234.0f, 1234.0f), nullptr, 0.0f);
}


Arena::~Arena()
{
}

void Arena::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
}
