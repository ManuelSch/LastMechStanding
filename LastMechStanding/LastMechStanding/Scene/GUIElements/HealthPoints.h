#pragma once

#include "GUIElement.h"


#define POS_X -0.95
#define POS_Y -0.9
#define POS_Z -1.0
#define WIDTH 0.03
#define HEIGHT 0.6

class HealthPoints : public GUIElement
{
public:
	HealthPoints();
	~HealthPoints();

	void setHealthPointsInPercent(GLfloat percent);
};

