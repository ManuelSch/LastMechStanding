#pragma once

#include "..\commonHeader.h"
#include "..\Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	enum Type {
		DIFFUSE,
		SPECULAR
	};
	GLuint id;
	Type type;
	aiString path;		// to check if it hasn't been loaded already
};


class Mesh
{
public:
	// mesh data:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void draw(Shader* shader);
	~Mesh();


private:
	GLuint VAO, VBO, EBO;	// render data

	void setupMesh();
};

