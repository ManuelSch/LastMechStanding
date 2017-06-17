#pragma once

#include "GUIElement.h"
#include "..\..\Util\Font.h"

class ViewFrustumCullingScreen : public GUIElement
{
public:
	ViewFrustumCullingScreen(shared_ptr<Font> font);
	~ViewFrustumCullingScreen();

	virtual void draw();
	virtual void update(GLfloat deltaTime);

	GLuint drawnElements = 0;

private:
	shared_ptr<Font> font;
};

