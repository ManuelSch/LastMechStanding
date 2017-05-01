#include "GUI.h"

GUI::GUI(GLfloat displayRatio)
{
	this->healthBar = make_shared<HealthBar>(displayRatio);
	this->crossHair = make_shared<Crosshair>(displayRatio);
	this->enemyHealthBar = make_shared<EnemyHealthBar>(displayRatio);
}

GUI::~GUI()
{
}

void GUI::update(GLfloat deltaTime)
{
	this->enemyHealthBar->update(deltaTime);
}


void GUI::draw()
{
	this->healthBar->draw();
	this->crossHair->draw();
	this->enemyHealthBar->draw();
}