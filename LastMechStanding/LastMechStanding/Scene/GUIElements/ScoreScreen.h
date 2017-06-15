#pragma once

#include "GUIElement.h"
#include "..\..\Util\Font.h"

class ScoreScreen : public GUIElement
{
public:
	ScoreScreen(shared_ptr<Font> font);
	~ScoreScreen();

	virtual void draw();
	virtual void update(GLfloat deltaTime);

	GLuint defeatedEnemies = 0;

private:
	shared_ptr<Font> font;
};

