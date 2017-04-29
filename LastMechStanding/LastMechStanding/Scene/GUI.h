#pragma once

/*
  Contains all GUI elements
*/

#include "../../commonHeader.h"
#include "./GUIElements/HealthBar.h"

class GUI
{
public:
	GUI();
	~GUI();

	shared_ptr<HealthBar> healthBar;
};