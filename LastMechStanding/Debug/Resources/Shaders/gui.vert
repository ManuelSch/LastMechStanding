#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoords;

out vec4 Color;
out vec2 TexCoords;

void main()
{
	gl_Position = vec4(position, 1.0f);
	Color = color;
	TexCoords = vec2(texCoords.x, 1.0 - texCoords.y);
}