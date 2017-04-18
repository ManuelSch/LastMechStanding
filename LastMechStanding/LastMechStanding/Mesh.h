#pragma once

#include "commonHeader.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;		// to check if it hasn't been loaded already
};

class Mesh
{
public:
	// mesh data:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	~Mesh();

private:
	GLuint VAO, VBO, EBO;	// render data

	void setupMesh();
};

