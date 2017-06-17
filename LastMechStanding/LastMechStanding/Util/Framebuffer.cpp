#include "Framebuffer.h"



Framebuffer::Framebuffer(shared_ptr<Display> _display) : display(_display)
{
	this->quad = make_shared<Quad>(display->getDisplayRatio(), ORIGIN, POSITION, WIDTH, HEIGHT, COLOR);
	this->shaderFinal = make_shared<Shader>("Resources/Shaders/bloom.vert", "Resources/Shaders/bloom.frag");
	this->shaderBlur = make_shared<Shader>("Resources/Shaders/gauss_blur.vert", "Resources/Shaders/gauss_blur.frag");

	this->shaderFinal->useShader();
	
	// generate the frame buffer object and bind it:
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

	// create a color attachment texture and attach it to the framebuffer:
	generateAttachmentTextures(false, false);

	// create renderbuffer object and bind it:
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
	// create a depth and stencil rbo:
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, display->width, display->height);
	// attach the renderbuffer object:
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rbo);

	// tell OpenGL we're rendering to multiple colorbuffers:
	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	// check if framebuffer has been completely initialized:
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "ERROR: Could not initialize framebuffer" << endl;
		return;
	}

	// initialize ping pong fbo's (for gauss blur):
	initPingPongFBO();

	// make the default framebuffer active again:
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


Framebuffer::~Framebuffer()
{
	// delete fbo:
	glDeleteFramebuffers(1, &fbo);
}

void Framebuffer::draw(shared_ptr<ShortKeys> shortKeys)
{
	this->shaderBlur->useShader();

	// apply gaussian blur to the brightColor-texture:
	GLboolean horizontal = true;
	const GLuint blurPasses = 20;		// 10x vertical + 10x horizontal
	for (GLuint i = 0; i < blurPasses; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingPongFBO[horizontal]);
		glUniform1i(shaderBlur->getUniformLocation("horizontal"), horizontal);

		// bind texture of other framebuffer (or scene if first iteration):
		if (i==0) {
			glBindTexture(GL_TEXTURE_2D, textureColorBuffers[1]);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, pingPongColorbuffers[!horizontal]);
		}

		this->quad->draw();

		horizontal = !horizontal;
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	this->shaderFinal->useShader();

	glUniform1i(shaderFinal->getUniformLocation("scene"), 0);
	glUniform1i(shaderFinal->getUniformLocation("bloomBlur"), 1);
	// bind texture:
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffers[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingPongColorbuffers[!horizontal]);
	glUniform1i(shaderFinal->getUniformLocation("bloom"), shortKeys->bloomOn);
	glUniform3f(shaderFinal->getUniformLocation("backgroundColor"), BACKGROUND_COLOR.x, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z);


	this->quad->draw();
}

void Framebuffer::generateAttachmentTextures(GLboolean depth, GLboolean stencil)
{
	// choose enum:
	GLenum attachment_type;
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;

	// generate texture IDs and load texture data:
	glGenTextures(2, textureColorBuffers);
	for (GLuint i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, textureColorBuffers[i]);

		if (!depth && !stencil) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, display->width, display->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, display->width, display->height, 0, GL_RGB, GL_FLOAT, NULL);
		}
		else {
			// using both a stencil and depth test -> needs special format arguments:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, display->width, display->height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// clamp to the edge; blur filter would otherwise sample repeated texture values:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// attach texture to framebuffer:
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureColorBuffers[i], 0);
	}
}

void Framebuffer::initPingPongFBO()
{
	// generate the ping pong frame buffer objects and textures:
	glGenFramebuffers(2, this->pingPongFBO);
	glGenTextures(2, this->pingPongColorbuffers);

	for (GLuint i = 0; i < 2; i++) {
		// bind the fbo and texture:
		glBindFramebuffer(GL_FRAMEBUFFER, pingPongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingPongColorbuffers[i]);

		// load texture data:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, display->width, display->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, display->width, display->height, 0, GL_RGB, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// clamp to the edge; blur filter would otherwise sample repeated texture values:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->pingPongColorbuffers[i], 0);

		// check if framebuffers are complete (no need for depth buffer):
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR: Could not initialize pingPongFramebuffer" << std::endl;
		}
	}
}
