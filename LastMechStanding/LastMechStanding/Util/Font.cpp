#include "Font.h"



Font::Font()
{
	this->shader = make_shared<Shader>("Resources/Shaders/freetype_glyph.vert", "Resources/Shaders/freetype_glyph.frag");

	// initialize freetype:
	if (FT_Init_FreeType(&this->ftLibrary)) {
		cout << "ERROR: Could not initialize freetype" << endl;
	}

	// load font:
	if (FT_New_Face(this->ftLibrary, "Resources/Fonts/goodtime.ttf", 0, &ftFace)) {
		cout << "ERROR: Could not load font" << endl;
	}

	// set font size:
	FT_Set_Pixel_Sizes(ftFace, 0, 48);

	// disable byte-alignment restriction:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// load glyphs for the first 128 ASCII characters:
	for (GLubyte c = 0; c < 128; c++) {
		// load character glyph:
		if (FT_Load_Char(ftFace, c, FT_LOAD_RENDER)) {
			cout << "ERROR: Could not load Glyph for c=" << c << endl;
			continue;
		}

		// generate texture:
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, ftFace->glyph->bitmap.buffer);	// the texture data is only stored in the red component

		// set texture options:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// store character for later use:
		Character character = {
			texture,
			glm::ivec2(ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows),
			glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
			ftFace->glyph->advance.x
		};
		this->characters.insert(std::pair<GLchar, Character>(c, character));
	}

	// clear freetype resources:
	FT_Done_Face(ftFace);
	FT_Done_FreeType(ftLibrary);

	// orthogonal projection matrix:
	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
	this->shader->useShader();
	glUniformMatrix4fv(this->shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// generate and bind VAO and VBO:
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


Font::~Font()
{
}

void Font::renderText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	this->shader->useShader();
	glUniform3d(this->shader->getUniformLocation("textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters:
	string::const_iterator c;
	int i=0;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		// update VBO for each character:
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		// render glyph texture over quad:
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// update content of VBO memory:
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		// render quad:
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// advance cursors for next glyph (advance is number of 1/64 pixels):
		x += (ch.advance >> 6) * scale;	// bitshift by 6 to get value in pixels (2^6 = 64)
	}


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
