#include "GUI.h"

GUI::GUI(GLfloat displayRatio)
{
	this->healthBar = make_shared<HealthBar>(displayRatio);
	this->crossHair = make_shared<Crosshair>(displayRatio);
}

GUI::~GUI()
{
}

void GUI::draw()
{
	this->healthBar->draw();
	this->crossHair->draw();
}
