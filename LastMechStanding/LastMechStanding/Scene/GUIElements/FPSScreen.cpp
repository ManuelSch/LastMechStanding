#include "FPSScreen.h"



FPSScreen::FPSScreen(shared_ptr<Font> font)
{
	this->font = font;
	this->fps = 0.0f;
}


FPSScreen::~FPSScreen()
{
}

void FPSScreen::draw()
{
	this->font->renderText("FPS: " + to_string((GLuint)fps), 400.0f, 10.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
}

void FPSScreen::update(GLfloat deltaTime)
{
	// calculate mean value so it doesn't flicker so much:
	//this->fps = (this->fps * 299.0f + 1.0f / deltaTime) / 300.0f;

	this->fps = 1.0f / deltaTime;
}
