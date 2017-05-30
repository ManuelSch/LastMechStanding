#version 330 core
in vec4 Color;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture;
uniform bool useTexture;

void main()
{
	if(useTexture) {
		color = vec4(texture(texture, TexCoords)) * vec4(Color);
	}
	else {
		color = vec4(Color);
	}
}