#pragma once

#include "GUIElement.h"

#define ORIGIN MIDDLE
#define POS_X 0
#define POS_Y 0
#define POS_Z -1.0
#define WIDTH 0.1
#define HEIGHT 0.1

class Crosshair : public GUIElement
{
public:
	Crosshair(GLfloat displayRatio);
	~Crosshair();
};

