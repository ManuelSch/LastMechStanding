#include "LoadingScreen.h"



LoadingScreen::LoadingScreen(shared_ptr<Font> font)
{
	this->font = font;
}


LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::draw(GLuint percent, shared_ptr<Display> display)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.45f, 0.78f, 1.0f, 1.0f);

	this->font->renderText("Loading: " + to_string(percent) + "\%", 10.0f, 10.0f, 0.6f, glm::vec3(1.0f, 1.0f, 1.0f));

	// swap window and frame buffer:
	glfwSwapBuffers(display->window);
}

void LoadingScreen::update(GLfloat deltaTime)
{
}
