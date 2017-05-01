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

void GUIElement::update(GLfloat deltaTime)
{
}

void GUIElement::useTexture(string filePath)
{
	// enable alpha (transparency):
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image(filePath.c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// set color to white so it doesn't interfere with the texture (default behaviour; color can be added by setting this->color afterwards)
	this->color = glm::vec4(1.0f);
	updateVertexData();

	// tell shader to render the texture:
	shader->useShader();
	glUniform1i(shader->getUniformLocation("useTexture"), 1);
}

// need to be called everytime the position, width, height or color are changed:
void GUIElement::updateVertexData()
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
