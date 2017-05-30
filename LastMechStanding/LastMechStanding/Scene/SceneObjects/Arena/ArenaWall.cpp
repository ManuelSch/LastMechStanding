#include "ArenaWall.h"



ArenaWall::ArenaWall(glm::vec3 position, GLboolean rotated)
{
	cout << "ArenaWall()" << endl;

	this->position = position;

	this->shader = make_shared<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_shared<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->simpleDepthShader = make_shared<Shader>("Resources/Shaders/simple_depth_shader.vert", "Resources/Shaders/simple_depth_shader.frag");

	if (rotated) {
		this->model = Model("Resources/Models/ArenaWall/arenaWall_rotated.obj");
	}
	else {
		this->model = Model("Resources/Models/ArenaWall/arenaWall.obj");
	}

	this->position.y = GROUND_LEVEL_Y;
}


ArenaWall::~ArenaWall()
{
}

void ArenaWall::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
}
