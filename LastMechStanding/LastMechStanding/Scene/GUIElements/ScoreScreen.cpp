#include "ScoreScreen.h"



ScoreScreen::ScoreScreen(shared_ptr<Font> font)
{
	this->font = font;
}


ScoreScreen::~ScoreScreen()
{
}

void ScoreScreen::draw()
{
	this->font->renderText("Defeated Enemies: " + to_string(defeatedEnemies), 10.0f, 10.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void ScoreScreen::update(GLfloat deltaTime)
{
}
