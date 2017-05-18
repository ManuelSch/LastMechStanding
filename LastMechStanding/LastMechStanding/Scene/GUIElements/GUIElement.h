#pragma once

#include "../../commonHeader.h"
#include "../../Util/Shader.h"
#include "../../Util/Quad.h"


class GUIElement
{
public:
	GUIElement();
	~GUIElement();

	virtual void draw();
	virtual void update(GLfloat deltaTime);


protected:
	shared_ptr<Shader> shader;
	shared_ptr<Quad> quad;
	GLuint texture;

	void useTexture(string filePath);
	glm::vec3 hsvToRgb(GLfloat h, GLfloat s, GLfloat v);
};