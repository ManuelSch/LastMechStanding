#include "ViewFrustumCullingScreen.h"



ViewFrustumCullingScreen::ViewFrustumCullingScreen(shared_ptr<Font> font)
{
	this->font = font;
}


ViewFrustumCullingScreen::~ViewFrustumCullingScreen()
{
}

void ViewFrustumCullingScreen::draw()
{
	this->font->renderText("Drawn Objects: " + to_string(drawnElements), 600.0f, 10.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void ViewFrustumCullingScreen::update(GLfloat deltaTime)
{
}
