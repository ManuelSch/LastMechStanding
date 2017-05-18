#pragma once

#include "GUIElement.h"


class Crosshair : public GUIElement
{
public:
	Crosshair(GLfloat displayRatio);
	~Crosshair();
	virtual void update(GLfloat deltaTime);

	void spread();

private:
	const Quad::Origin ORIGIN = Quad::MIDDLE;
	const glm::vec3 POSITION = glm::vec3(0, 0, -1.0);
	const GLfloat WIDTH = 0.1;
	const GLfloat HEIGHT = 0.1;
	const glm::vec4 COLOR = glm::vec4(1.0f);

	GLfloat size;
};

