#include "Framebuffer.h"



Framebuffer::Framebuffer(shared_ptr<Display> _display) : display(_display)
{
	this->quad = make_shared<Quad>(display->getDisplayRatio(), ORIGIN, POSITION, WIDTH, HEIGHT, COLOR);
	this->shader = make_shared<Shader>("Resources/Shaders/quad.vert", "Resources/Shaders/quad.frag");
	
	// generate the frame buffer object and bind it:
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

	/* Use texture attachment: *//*
	// create a texture...
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, display->width, display->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// attach a depth (24bit) and stencil (8 bit) buffer:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, display->width, display->height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->texture, 0);
	/**/

	/* Use renderbuffer object attachment: *//*
	// create renderbuffer object and bind it:
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
	// create a depth and stencil rbo:
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, display->width, display->height);
	// attach the renderbuffer object:
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
	/**/

	// create a color attachment texture and attach it to the framebuffer:
	this->textureColorBuffer = generateAttachmentTexture(false, false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureColorBuffer, 0);

	// create renderbuffer object and bind it:
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
	// create a depth and stencil rbo:
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, display->width, display->height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	// attach the renderbuffer object:
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);


	// check if framebuffer has been completely initialized:
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "ERROR: Could not initialize framebuffer" << endl;
		return;
	}

	// make the default framebuffer active again:
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->shader->useShader();
	glUniform1i(shader->getUniformLocation("useTexture"), 1);
}


Framebuffer::~Framebuffer()
{
	// delete fbo:
	glDeleteFramebuffers(1, &fbo);
}

void Framebuffer::draw()
{
	this->shader->useShader();

	// bind texture:
	glBindTexture(GL_TEXTURE_2D, this->textureColorBuffer);

	this->quad->draw();
}

GLuint Framebuffer::generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	// choose enum:
	GLenum attachment_type;
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;

	// generate texture ID and load texture data :
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (!depth && !stencil) {
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, display->width, display->height, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	}
	else {
		// using both a stencil and depth test -> needs special format arguments:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, display->width, display->height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
