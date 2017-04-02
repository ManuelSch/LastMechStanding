#include "Cube.h"
using namespace scene;

#ifdef SCENE_OBJECT


using namespace util;


Cube::Cube() : SceneObject() {
}


Cube::Cube(glm::mat4& matrix, Shader* _shader)
	: SceneObject(matrix), shader(_shader) {
	
	bool res = loadOBJ("./Resources/Models/Cube/cube.object", positions, uvs, normals);

	// Load data to buffer:
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	/* ueberbleibsel aus dem cg-tutorial - noch benoetigt?
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::vec3), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	*/
	glGenBuffers(1, &normalsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(unsigned int), &normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	// Generate bindings:
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	auto positionIndex = glGetAttribLocation(shader->programHandle, "position");
	glEnableVertexAttribArray(positionIndex);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	auto normalIndex = glGetAttribLocation(shader->programHandle, "normal");
	glEnableVertexAttribArray(normalIndex);
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	auto uvIndex = glGetAttribLocation(shader->programHandle, "uv");
	glEnableVertexAttribArray(uvIndex);
	glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

	/* ueberbleibsel aus dem cg-tutorial - noch benoetigt?
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


Cube::~Cube() {
	glDeleteBuffers(1, &normalsBuffer);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vao);
}

void Cube::update(float time_delta) {
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f) * time_delta, glm::vec3(0, 1, 0));
}

void Cube::draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, positions.size() * sizeof(glm::vec3));
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


/*
const float Cube::POSITIONS[24 * 3] = {
	// Back
	-0.5f,-0.5f,-0.5f,
	-0.5f,0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,

	// Front
	-0.5f,-0.5f,0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,0.5f,0.5f,
	-0.5f,0.5f,0.5f,

	// Top
	0.5f,0.5f,0.5f,
	0.5f,0.5f,-0.5f,
	-0.5f,0.5f,-0.5f,
	-0.5f,0.5f,0.5f,

	// Bottom
	0.5f,-0.5f,0.5f,
	-0.5f,-0.5f,0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,

	// Right
	0.5f,0.5f,0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,0.5f,-0.5f,

	// Left
	-0.5f,0.5f,0.5f,
	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,0.5f

};

const unsigned int Cube::INDICES[36] = {
	0,1,2,
	0,2,3,

	4,5,6,
	4,6,7,

	8,9,10,
	8,10,11,

	12,13,14,
	12,14,15,

	16,17,18,
	16,18,19,

	20,21,22,
	20,22,23
};

const float Cube::NORMALS[24 * 3] = {
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
};

const float Cube::UVS[24 * 2] = {
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
};
*/
#endif