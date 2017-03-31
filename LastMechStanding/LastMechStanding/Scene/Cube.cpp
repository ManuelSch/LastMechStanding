#include "Cube.h"
using namespace scene;

#ifdef SCENE_OBJECT


using namespace util;


Cube::Cube() : SceneObject() {
}

Cube::Cube(std::string& fileName) : SceneObject() {


	// TODO: Hier weitermachen mit Model einbinden:
	// siehe https://www.youtube.com/watch?v=NS980twY1ZE (ab 6:28)
	//IndexedModel model = OBJModel(fileName).ToIndexedModel();

}


void InitMesh(const IndexedModel& model) {

}


Cube::Cube(glm::mat4& matrix, Shader* _shader)
	: SceneObject(matrix), shader(_shader) {

	// Load data to buffer:
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec3), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec3), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalsBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), normals, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}


Cube::~Cube() {
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vao);
}

void Cube::update(float time_delta) {
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f) * time_delta, glm::vec3(0, 1, 0));
}

void Cube::draw() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

const float old_positions[24 * 3] = {
	0.5f,0.5f,0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f,

	-0.5f,0.5f,0.5f,
	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,0.5f
};

const float Cube::positions[24 * 3] = {
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

const unsigned int old_indices[36] = {
	0,1,2,
	0,2,3,

	4,5,6,
	4,6,7,

	0,1,4,
	1,5,4,

	2,3,6,
	3,7,6,

	1,2,6,
	1,6,5,

	0,4,7,
	0,7,3
};

const unsigned int Cube::indices[36] = {
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

const float Cube::normals[24 * 3] = {
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

#endif