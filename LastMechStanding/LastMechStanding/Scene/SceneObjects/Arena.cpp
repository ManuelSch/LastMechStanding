#include "Arena.h"



Arena::Arena()
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_unique<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->model = Model("Resources/Models/ArenaTest/arenaTest.obj");
}


Arena::~Arena()
{
}

void Arena::update(float deltaTime)
{
}
