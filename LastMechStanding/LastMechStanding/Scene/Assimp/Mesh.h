#pragma once

#include "..\..\commonHeader.h"
#include "..\..\Util\Shader.h"
#include "..\..\Util\BoundingBox.h"
#include "..\..\Game\ShortKeys.h"

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
	
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, shared_ptr<BoundingBox> boundingBox);
	void draw(Shader* shader, ShortKeys* shortKeys);
	~Mesh();


private:
	GLuint VAO, VBO, EBO;	// render data

	void setupMesh();

	ShortKeys::MipMappingQuality lastMMQuality = ShortKeys::MipMappingQuality::LINEAR;
};

