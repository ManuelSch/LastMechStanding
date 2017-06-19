#pragma once

#include "GUIElement.h"
#include "..\..\Util\Font.h"
#include "..\..\Game\Display.h"

class LoadingScreen : public GUIElement
{
public:
	LoadingScreen(shared_ptr<Font> font);
	~LoadingScreen();

	virtual void draw(GLuint percent, shared_ptr<Display> display);
	virtual void update(GLfloat deltaTime);

private:
	shared_ptr<Font> font;
};

