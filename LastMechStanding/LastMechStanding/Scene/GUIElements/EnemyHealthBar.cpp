#include "EnemyHealthBar.h"


EnemyHealthBar::EnemyHealthBar(GLfloat displayRatio)
{
	this->quad = make_shared<Quad>(displayRatio, ORIGIN, POSITION, WIDTH, HEIGHT, COLOR);
	this->shader = make_shared<Shader>("Resources/Shaders/quad.vert", "Resources/Shaders/quad.frag");

	this->opacity = 0.0f;

	// use this method if you want to display a texture on the gui element:
	//useTexture("Resources/Textures/container.jpg");

	setHealthPointsInPercent(1.0f);
	quad->updateVertexData();
}

EnemyHealthBar::~EnemyHealthBar()
{
}

void EnemyHealthBar::update(GLfloat deltaTime)
{
	this->opacity -= 1.0f * deltaTime;
	this->opacity = max(0.0f, opacity);

	quad->color.w = min(0.5f, opacity);

	quad->updateVertexData();
}

void EnemyHealthBar::setHealthPointsInPercent(GLfloat percent)
{
	this->opacity = 1.5f;

	quad->width = WIDTH * percent;

	// gradually turn color from green to red:
	quad->color = glm::vec4(this->hsvToRgb(percent * 110.0f - 20.0f, 255, 255), 0.8f);

	quad->updateVertexData();
}
