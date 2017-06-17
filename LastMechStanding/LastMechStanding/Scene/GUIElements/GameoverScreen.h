#pragma once

#include "GUIElement.h"
#include "..\..\Util\Font.h"

class GameoverScreen : public GUIElement
{
public:
	GameoverScreen(shared_ptr<Font> font);
	~GameoverScreen();

	virtual void draw(GLuint defeatedEnemies);
	virtual void update(GLfloat deltaTime);

private:
	shared_ptr<Font> font;
};

