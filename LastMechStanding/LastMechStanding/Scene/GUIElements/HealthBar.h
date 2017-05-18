#pragma once

#include "GUIElement.h"


class HealthBar : public GUIElement
{
public:

	HealthBar(GLfloat displayRatio);
	~HealthBar();

	void setHealthPointsInPercent(GLfloat percent);

private:
	const Quad::Origin ORIGIN = Quad::BOTTOM_LEFT;
	const glm::vec3 POSITION = glm::vec3(-0.95, -0.9, -1.0);
	const GLfloat WIDTH = 0.03;
	const GLfloat HEIGHT = 0.6;
	const glm::vec4 COLOR = glm::vec4(1.0f);
};

