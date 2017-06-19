#include "Lamp.h"

Lamp::Lamp()
{
	cout << "Lamp()" << endl;

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/CubeEnemy/cubeEnemy.dae");
}


Lamp::~Lamp()
{
}

void Lamp::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
}
