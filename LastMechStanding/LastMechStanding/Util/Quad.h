#pragma once

#include "..\commonHeader.h"

class Quad
{
public:
	enum Origin {
		MIDDLE,
		BOTTOM_LEFT,
		FULLSCREEN
	};

	Quad(GLfloat displayRatio, Origin origin, glm::vec3 position, GLfloat width, GLfloat height, glm::vec4 color);
	~Quad();

	// vertex data (call updateVertexData() when changing these!):
	glm::vec3 position;
	GLfloat width, height;
	glm::vec4 color;

	void updateVertexData();
	void draw();

	Origin origin;
	GLfloat displayRatio;

	GLuint VAO, VBO, EBO;
};

