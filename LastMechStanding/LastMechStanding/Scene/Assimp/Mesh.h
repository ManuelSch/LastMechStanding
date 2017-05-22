#pragma once

#include "..\..\commonHeader.h"
#include "..\..\Util\Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;		// to check if it hasn't been loaded already
};


class Mesh
{
public:
	// mesh data:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	glm::vec3 minimumBB;
	glm::vec3 maximumBB;
	
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void draw(Shader* shader);
	~Mesh();


private:
	GLuint VAO, VBO, EBO;	// render data

	void setupMesh();
};

