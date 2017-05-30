#include "Container1.h"



Container1::Container1(glm::vec3 position)
{
	cout << "Container1()" << endl;

	this->position = position;

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	if ((GLfloat)((double)rand() / (double)RAND_MAX) >= 0.5) {
		this->model = Model("Resources/Models/Container/container.obj");
	}
	else {
		this->model = Model("Resources/Models/Container/container2.obj");
	}

	this->scale(glm::vec3(((GLfloat)((double)rand() / (double)RAND_MAX) * 6.0f + 1.0f), ((GLfloat)((double)rand() / (double)RAND_MAX) * 2.0f + 1.0f), ((GLfloat)((double)rand() / (double)RAND_MAX) * 12.0f + 1.0f)));

	this->position.y = GROUND_LEVEL_Y;
}


Container1::~Container1()
{
}

void Container1::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
}
