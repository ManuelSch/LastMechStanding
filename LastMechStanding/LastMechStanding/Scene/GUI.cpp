#include "GUI.h"

GUI::GUI(GLfloat displayRatio, shared_ptr<ShortKeys> shortKeys, shared_ptr<Font> font)
{
	this->shortKeys = shortKeys;

	this->healthBar = make_shared<HealthBar>(displayRatio);
	this->crossHair = make_shared<Crosshair>(displayRatio);
	this->enemyHealthBar = make_shared<EnemyHealthBar>(displayRatio);
	this->fpsScreen = make_shared<FPSScreen>(font);
	this->scoreScreen = make_shared<ScoreScreen>(font);
}

GUI::~GUI()
{
}

void GUI::update(GLfloat deltaTime)
{
	this->enemyHealthBar->update(deltaTime);
	this->crossHair->update(deltaTime);
	this->fpsScreen->update(deltaTime);
	this->scoreScreen->update(deltaTime);
}


void GUI::draw()
{
	this->crossHair->draw();
	this->healthBar->draw();
	this->enemyHealthBar->draw();
	if (this->shortKeys->frameTimeOn) {
		this->fpsScreen->draw();
	}
	this->scoreScreen->draw();
}