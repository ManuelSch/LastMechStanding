#include "Crosshair.h"



Crosshair::Crosshair(GLfloat displayRatio)
{
	this->quad = make_shared<Quad>(displayRatio, ORIGIN, POSITION, WIDTH, HEIGHT, COLOR);
	this->shader = make_shared<Shader>("Resources/Shaders/quad.vert", "Resources/Shaders/quad.frag");

	// use this method if you want to display a texture on the gui element:
	useTexture("Resources/Textures/crosshair.png");
	quad->color = glm::vec4(0.7f, 0.6f, 0.05f, 1.0f);

	quad->updateVertexData();
}


Crosshair::~Crosshair()
{
}

void Crosshair::update(GLfloat deltaTime)
{
	quad->width -= deltaTime*.1;
	quad->width = max((float)WIDTH, quad->width);
	quad->height = quad->width;

	quad->updateVertexData();
}

void Crosshair::spread()
{
	quad->width = WIDTH * 1.8f;
	quad->height = quad->width;

	quad->updateVertexData();
}

