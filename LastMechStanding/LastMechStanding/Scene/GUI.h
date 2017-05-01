#pragma once

/*
  Contains all GUI elements
*/

#include "../../commonHeader.h"
#include "./GUIElements/HealthBar.h"
#include "./GUIElements/Crosshair.h"
#include "./GUIElements/EnemyHealthBar.h"

class GUI
{
public:
	GUI(GLfloat displayRatio);
	~GUI();

	shared_ptr<HealthBar> healthBar;
	shared_ptr<Crosshair> crossHair;
	shared_ptr<EnemyHealthBar> enemyHealthBar;

	void update(GLfloat deltaTime);
	void draw();

private:
};