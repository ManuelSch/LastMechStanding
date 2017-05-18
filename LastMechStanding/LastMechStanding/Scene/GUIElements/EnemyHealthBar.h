#pragma once

#include "GUIElement.h"



class EnemyHealthBar : public GUIElement
{
public:

	EnemyHealthBar(GLfloat displayRatio);
	~EnemyHealthBar();

	virtual void update(GLfloat deltaTime);

	void setHealthPointsInPercent(GLfloat percent);

private:
	const Quad::Origin ORIGIN = Quad::MIDDLE;
	const glm::vec3 POSITION = glm::vec3(0, -0.12, -1.0);
	const GLfloat WIDTH = 0.15;
	const GLfloat HEIGHT = 0.025;
	const glm::vec4 COLOR = glm::vec4(1.0f);

	GLfloat opacity;
};

