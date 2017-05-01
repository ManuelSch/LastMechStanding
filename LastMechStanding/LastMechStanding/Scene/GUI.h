#pragma once

/*
  Contains all GUI elements
*/

#include "../../commonHeader.h"
#include "./GUIElements/HealthBar.h"
#include "./GUIElements/Crosshair.h"

class GUI
{
public:
	GUI(GLfloat displayRatio);
	~GUI();

	shared_ptr<HealthBar> healthBar;
	shared_ptr<Crosshair> crossHair;

	void draw();

private:
};