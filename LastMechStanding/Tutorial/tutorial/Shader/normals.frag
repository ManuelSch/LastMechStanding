#version 330

in vec3 worldNormal;

layout(location=0) out vec4 fragColor;

void main() {
	fragColor = vec4((worldNormal + 1) / 2, 1.0);
}