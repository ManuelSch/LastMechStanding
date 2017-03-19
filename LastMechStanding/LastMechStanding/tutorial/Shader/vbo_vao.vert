#version 330

in vec3 position;
in vec3 normal;

out vec3 fragNormal;

uniform mat4 model;

void main() {
	fragNormal = (model * vec4(normal, 0)).xyz;
	gl_Position = model * vec4(position, 1);
}