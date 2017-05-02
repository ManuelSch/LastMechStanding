#include "HealthBar.h"



HealthBar::HealthBar(GLfloat displayRatio)
{
	this->displayRatio = displayRatio;

	this->origin = ORIGIN;

	this->position = glm::vec3(POS_X, POS_Y, POS_Z);
	this->width = WIDTH;
	this->height = HEIGHT;
	this->color = glm::vec4(1.0f);

	this->shader = make_unique<Shader>("Resources/Shaders/gui.vert", "Resources/Shaders/gui.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// use this method if you want to display a texture on the gui element:
	//useTexture("Resources/Textures/container.jpg");

	setHealthPointsInPercent(1.0f);
	updateVertexData();
}

HealthBar::~HealthBar()
{
}

void HealthBar::setHealthPointsInPercent(GLfloat percent)
{
	this->height = HEIGHT * percent;

	// gradually turn color from green to red:
	this->color = glm::vec4(this->hsvToRgb(percent * 110.0f - 20.0f, 255, 255), 0.7f);

	updateVertexData();
}
