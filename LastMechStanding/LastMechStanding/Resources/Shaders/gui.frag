#version 330 core
in vec3 Color;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture;
uniform bool useTexture;

void main()
{
	if(useTexture) {
		color = texture(texture, TexCoords) * vec4(Color, 1.0f);
	}
	else {
		color = vec4(Color, 0.5f);
	}
}