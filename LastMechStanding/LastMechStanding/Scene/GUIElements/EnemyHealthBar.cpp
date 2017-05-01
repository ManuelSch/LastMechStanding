#include "EnemyHealthBar.h"


EnemyHealthBar::EnemyHealthBar(GLfloat displayRatio)
{
	this->displayRatio = displayRatio;

	this->origin = ORIGIN;

	this->position = glm::vec3(POS_X, POS_Y, POS_Z);
	this->width = WIDTH;
	this->height = HEIGHT;
	this->color = glm::vec4(1.0f);

	this->shader = make_unique<Shader>("Resources/Shaders/gui.vert", "Resources/Shaders/gui.frag");

	this->opacity = 0.0f;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// use this method if you want to display a texture on the gui element:
	//useTexture("Resources/Textures/container.jpg");

	setHealthPointsInPercent(1.0f);
	updateVertexData();
}

EnemyHealthBar::~EnemyHealthBar()
{
}

void EnemyHealthBar::update(GLfloat deltaTime)
{
	this->opacity -= 1.0f * deltaTime;
	this->opacity = max(0.0f, opacity);

	this->color.w = min(0.5f, opacity);

	updateVertexData();
}

void EnemyHealthBar::setHealthPointsInPercent(GLfloat percent)
{
	this->opacity = 1.5f;

	this->width = WIDTH * percent;

	if (percent > 0.3f) {
		this->color = glm::vec4(0.0f, 1.0f, 0.0f, min(0.5f, opacity));
	}
	else {
		this->color = glm::vec4(1.0f, 0.0f, 0.0f, min(0.5f, opacity));
	}

	updateVertexData();
}
