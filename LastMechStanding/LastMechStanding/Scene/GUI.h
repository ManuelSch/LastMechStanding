#pragma once

/*
  Contains all GUI elements
*/

#include "../../commonHeader.h"
#include "./GUIElements/HealthPoints.h"

class GUI
{
public:
	GUI();
	~GUI();

	shared_ptr<HealthPoints> healthPoints;
};