#include "Quad.h"



Quad::Quad(GLfloat displayRatio, Origin origin, glm::vec3 position, GLfloat width, GLfloat height, glm::vec4 color)
{
	this->displayRatio = displayRatio;
	this->origin = origin;
	this->position = position;
	this->width = width;
	this->height = height;
	this->color = color;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	updateVertexData();
}


Quad::~Quad()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

// needs to be called everytime the position, width, height or color are changed:
void Quad::updateVertexData()
{
	glBindVertexArray(VAO);

	switch (this->origin) {
		case MIDDLE:
		{
			GLfloat vertices[36] = {
				// Positions																	// Colors								// Texture Coords
				position.x + (width / 2) / displayRatio, position.y + height / 2, position.z,	color.x, color.y, color.z, color.w,		1.0f, 1.0f, // Top Right
				position.x + (width / 2) / displayRatio, position.y - height / 2, position.z,	color.x, color.y, color.z, color.w,		1.0f, 0.0f, // Bottom Right
				position.x - (width / 2) / displayRatio, position.y - height / 2, position.z,	color.x, color.y, color.z, color.w,		0.0f, 0.0f, // Bottom Left
				position.x - (width / 2) / displayRatio, position.y + height / 2, position.z,	color.x, color.y, color.z, color.w,		0.0f, 1.0f  // Top Left 
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			break;
		}
		case BOTTOM_LEFT:
		{
			GLfloat vertices[36] = {
				// Positions																		// Colors						// Texture Coords
				position.x + width / displayRatio, position.y + height, position.z,			color.x, color.y, color.z, color.w,		1.0f, 1.0f, // Top Right
				position.x + width / displayRatio, position.y,			position.z,			color.x, color.y, color.z, color.w,		1.0f, 0.0f, // Bottom Right
				position.x,						   position.y,			position.z,			color.x, color.y, color.z, color.w,		0.0f, 0.0f, // Bottom Left
				position.x,						   position.y + height, position.z,			color.x, color.y, color.z, color.w,		0.0f, 1.0f  // Top Left 
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			break;
		}
		case FULLSCREEN:
		{
			GLfloat vertices[36] = {
				// Positions																		// Colors						// Texture Coords
				1.0f, 1.0f, 0.0f,		color.x, color.y, color.z, color.w,		1.0f, 0.0f, // Top Right
				1.0f, -1.0f, 0.0f,		color.x, color.y, color.z, color.w,		1.0f, 1.0f, // Bottom Right
				-1.0f, -1.0f, 0.0f,		color.x, color.y, color.z, color.w,		0.0f, 1.0f, // Bottom Left
				-1.0f,  1.0f, 0.0f,		color.x, color.y, color.z, color.w,		0.0f, 0.0f  // Top Left 
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			break;
		}
	}

	GLuint indices[6] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Quad::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
