#include "GameoverScreen.h"



GameoverScreen::GameoverScreen(shared_ptr<Font> font)
{
	this->font = font;
}


GameoverScreen::~GameoverScreen()
{
}

void GameoverScreen::draw(GLuint defeatedEnemies)
{
	this->font->renderText("GAME OVER", 10.0f, 100.0f, 0.6f, glm::vec3(1.0f, 1.0f, 1.0f));
	this->font->renderText("Highscore: " + to_string(defeatedEnemies) + " defeated Enemies", 10.0f, 10.0f, 0.6f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameoverScreen::update(GLfloat deltaTime)
{
}
