#include "GUIElement.h"



GUIElement::GUIElement()
{
}


GUIElement::~GUIElement()
{
}

void GUIElement::draw()
{
	shader->useShader();

	// bind Textures using texture units:
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shader->getUniformLocation("texture"), 0);

	// draw container:
	this->quad->draw();
}

void GUIElement::update(GLfloat deltaTime)
{
}

void GUIElement::useTexture(string filePath)
{
	// create a texture:
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set texture parameters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load, create texture and generate mipmaps:
	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image(filePath.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// set color to white so it doesn't interfere with the texture (default behaviour; color can be added by setting this->color afterwards)
	this->quad->color = glm::vec4(1.0f);
	this->quad->updateVertexData();

	// tell shader to render the texture:
	shader->useShader();
	glUniform1i(shader->getUniformLocation("useTexture"), 1);
}

glm::vec3 GUIElement::hsvToRgb(GLfloat h, GLfloat s, GLfloat v) {
	h = max(0.0f, h);
	s = max(0.0f, s);
	v = max(0.0f, v);

	h /= 255.0f;
	s /= 255.0f;
	v /= 255.0f;
	GLfloat r, g, b;

	GLint i = floor(h * 6);
	GLfloat f = h * 6 - i;
	GLfloat p = v * (1 - s);
	GLfloat q = v * (1 - f * s);
	GLfloat t = v * (1 - (1 - f) * s);

	switch (i % 6) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}

	return glm::vec3(r, g, b);
}