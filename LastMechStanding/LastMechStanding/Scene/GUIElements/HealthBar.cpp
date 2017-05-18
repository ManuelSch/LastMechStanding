#include "HealthBar.h"



HealthBar::HealthBar(GLfloat displayRatio)
{
	this->quad = make_shared<Quad>(displayRatio, ORIGIN, POSITION, WIDTH, HEIGHT, COLOR);
	this->shader = make_shared<Shader>("Resources/Shaders/quad.vert", "Resources/Shaders/quad.frag");

	// use this method if you want to display a texture on the gui element:
	//useTexture("Resources/Textures/container.jpg");

	setHealthPointsInPercent(1.0f);
	quad->updateVertexData();
}

HealthBar::~HealthBar()
{
}

void HealthBar::setHealthPointsInPercent(GLfloat percent)
{
	this->quad->height = HEIGHT * percent;

	// gradually turn color from green to red:
	this->quad->color = glm::vec4(this->hsvToRgb(percent * 110.0f - 20.0f, 255, 255), 0.7f);

	this->quad->updateVertexData();
}
