#pragma once

/*
  Contains all GUI elements
*/

#include "../../commonHeader.h"
#include "../Util/Font.h"
#include "../Game/ShortKeys.h"
#include "./GUIElements/HealthBar.h"
#include "./GUIElements/Crosshair.h"
#include "./GUIElements/EnemyHealthBar.h"
#include "./GUIElements/FPSScreen.h"

class GUI
{
public:
	GUI(GLfloat displayRatio, shared_ptr<ShortKeys> shortKeys, shared_ptr<Font> font);
	~GUI();

	shared_ptr<ShortKeys> shortKeys;

	shared_ptr<HealthBar> healthBar;
	shared_ptr<Crosshair> crossHair;
	shared_ptr<EnemyHealthBar> enemyHealthBar;
	shared_ptr<FPSScreen> fpsScreen;

	void update(GLfloat deltaTime);
	void draw();

private:
};