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
}

EnemyTop::~EnemyTop()
{
}

void EnemyTop::update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	this->position = parent->position;

	this->angle.y = this->calculateAngle(position.x, position.z, player->position.x, player->position.z);
}

void EnemyTop::onClick()
{
	this->parent->onClick();
}
