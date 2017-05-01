#include "Crosshair.h"



Crosshair::Crosshair(GLfloat displayRatio)
{
	this->displayRatio = displayRatio;

	this->origin = ORIGIN;

	this->position = glm::vec3(POS_X, POS_Y, POS_Z);
	this->width = WIDTH;
	this->height = HEIGHT;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);

	this->shader = make_unique<Shader>("Resources/Shaders/gui.vert", "Resources/Shaders/gui.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// use this method if you want to display a texture on the gui element:
	useTexture("Resources/Textures/crosshair.png");
	this->color = glm::vec3(0.7f, 0.7f, 0.05f);

	updateVertexData();
}


Crosshair::~Crosshair()
{
}
