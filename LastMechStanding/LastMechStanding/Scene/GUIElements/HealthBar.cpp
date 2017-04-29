#include "HealthBar.h"



HealthBar::HealthBar()
{
	this->position = glm::vec3(POS_X, POS_Y, POS_Z);
	this->width = WIDTH;
	this->height = HEIGHT;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);

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


	if (percent > 0.3f) {
		this->color = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		this->color = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	updateVertexData();
}
