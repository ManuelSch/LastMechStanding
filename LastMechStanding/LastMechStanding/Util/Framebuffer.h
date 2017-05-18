#pragma once

#include "..\commonHeader.h"
#include "..\Game\Display.h"
#include "..\Util\Shader.h"
#include "..\Util\Quad.h"

class Framebuffer
{
public:
	Framebuffer(shared_ptr<Display> _display);
	~Framebuffer();

	GLuint fbo;					// Frame buffer object
	GLuint textureColorBuffer;	// texture attachment
	GLuint rbo;					// renderbuffer object attachment

	shared_ptr<Display> display;
	shared_ptr<Shader> shader;
	shared_ptr<Quad> quad;

	void draw();
	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

private:
	const Quad::Origin ORIGIN = Quad::FULLSCREEN;
	const glm::vec3 POSITION = glm::vec3(0, 0, 0);
	const GLfloat WIDTH = 2;
	const GLfloat HEIGHT = 2;
	const glm::vec4 COLOR = glm::vec4(1.0f);
};

