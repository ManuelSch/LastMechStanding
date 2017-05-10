#pragma once

#include "..\commonHeader.h"
#include "..\Util\Shader.h"

class Font
{
public:
	struct Character {
		GLuint textureID;	// ID of the glyph texture
		glm::ivec2 size;	// glyph size
		glm::ivec2 bearing;	// offset from baseline to left/top of the glyph
		GLuint advance;		// offset to advance to next glyph
	};

	Font();
	~Font();

	void renderText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
	FT_Library ftLibrary;
	FT_Face ftFace;

	map<GLchar, Character> characters;
	GLuint VAO, VBO;
	shared_ptr<Shader> shader;
};

