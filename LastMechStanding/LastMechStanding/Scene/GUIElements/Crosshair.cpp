#include "Crosshair.h"



Crosshair::Crosshair(GLfloat displayRatio)
{
	this->displayRatio = displayRatio;

	this->origin = ORIGIN;

	this->position = glm::vec3(POS_X, POS_Y, POS_Z);
	this->width = WIDTH;
	this->height = HEIGHT;
	this->color = glm::vec4(1.0f);

	this->shader = make_shared<Shader>("Resources/Shaders/gui.vert", "Resources/Shaders/gui.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// use this method if you want to display a texture on the gui element:
	useTexture("Resources/Textures/crosshair.png");
	this->color = glm::vec4(0.7f, 0.6f, 0.05f, 1.0f);

	updateVertexData();
}


Crosshair::~Crosshair()
{
}

void Crosshair::update(GLfloat deltaTime)
{
	this->width -= deltaTime*.1;
	this->width = max((float)WIDTH, width);
	this->height = this->width;

	updateVertexData();
}

void Crosshair::spread()
{
	this->width = WIDTH * 1.8f;
	this->height = this->width;

	updateVertexData();
}

