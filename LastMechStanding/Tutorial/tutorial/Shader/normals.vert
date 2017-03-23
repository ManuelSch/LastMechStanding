#version 330

in vec3 position;
in vec3 normal;

out vec3 worldNormal;

uniform mat4 model;

void main() {
	worldNormal = (model * vec4(normal, 0)).xyz;
	gl_Position = model * vec4(position, 1);
}