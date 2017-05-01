#pragma once

#include "../../commonHeader.h"
#include "../../Util/Shader.h"


class GUIElement
{
public:
	GUIElement();
	~GUIElement();

	virtual void draw();
	virtual void update(GLfloat deltaTime);

protected:
	enum Origin {
		MIDDLE,
		BOTTOM_LEFT
	};

	unique_ptr<Shader> shader;
	GLuint VBO, VAO, EBO;
	GLuint texture;

	Origin origin;
	GLfloat displayRatio;

	// vertex data (call updateVertexData() when changing these!):
	glm::vec3 position;
	GLfloat width, height;
	glm::vec4 color;

	void useTexture(string filePath);
	void updateVertexData();
};