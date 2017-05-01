#pragma once

#include "GUIElement.h"


#define ORIGIN MIDDLE
#define POS_X 0
#define POS_Y -0.12
#define POS_Z -1.0
#define WIDTH 0.15
#define HEIGHT 0.025

class EnemyHealthBar : public GUIElement
{
public:

	EnemyHealthBar(GLfloat displayRatio);
	~EnemyHealthBar();

	virtual void update(GLfloat deltaTime);

	void setHealthPointsInPercent(GLfloat percent);

private:
	GLfloat opacity;
};

