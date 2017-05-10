#pragma once

#include "GUIElement.h"
#include "..\..\Util\Font.h"

class FPSScreen : public GUIElement
{
public:
	FPSScreen(shared_ptr<Font> font);
	~FPSScreen();

	virtual void draw();
	virtual void update(GLfloat deltaTime);

private:
	GLfloat fps;
	shared_ptr<Font> font;
};

