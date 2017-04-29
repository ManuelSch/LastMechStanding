#include "GUIElement.h"



GUIElement::GUIElement()
{
}


GUIElement::~GUIElement()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void GUIElement::draw()
{
	shader->useShader();

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(shader->getUniformLocation("texture"), 0);

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void GUIElement::useTexture(string filePath)
{
	// Load and create a texture:
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // set color to white so it doesn't interfere with the texture (default behaviour; color can be added by calling setColor() afterwards)
	this->color = glm::vec3(1.0f);
	updateVertexData();

	// tell shader to render the texture:
	shader->useShader();
	glUniform1i(shader->getUniformLocation("useTexture"), 1);
}

// need to be called everytime the position, width, height or color are changed:
void GUIElement::updateVertexData()
{
	GLfloat vertices[32] = {
		// Positions											// Colors						// Texture Coords
		position.x + width, position.y + height, position.z,	color.x, color.y, color.z,		1.0f, 1.0f, // Top Right
		position.x + width, position.y,			 position.z,	color.x, color.y, color.z,		1.0f, 0.0f, // Bottom Right
		position.x,			position.y,			 position.z,	color.x, color.y, color.z,		0.0f, 0.0f, // Bottom Left
		position.x,			position.y + height, position.z,	color.x, color.y, color.z,		0.0f, 1.0f  // Top Left 
	};

	GLuint indices[6] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
