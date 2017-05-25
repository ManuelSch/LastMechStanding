#include "Arena.h"


Arena::Arena()
{
	cout << "Arena()" << endl;

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	this->model = Model("Resources/Models/Arena/arena.obj");
}


Arena::~Arena()
{
}

void Arena::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
}
