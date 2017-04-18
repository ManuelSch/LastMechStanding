#include "Mesh.h"


Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}

void Mesh::Draw(Shader* shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;

	for (GLuint i = 0; i < this->textures.size(); i++) {

		// activate texture unit before binding:
		glActiveTexture(GL_TEXTURE0 + i);

		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse") {
			ss << diffuseNr++;
		}
		else if (name == "texture_specular") {
			ss << specularNr++;
		}
		number = ss.str();

		glUniform1f(shader->getUniformLocation("material." + name + number), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	// draw mesh:
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
}

void Mesh::setupMesh()
{
	// generate the VAO, VBO and EBO:
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	// bind the VAO, VBO and EBO:
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	// apply the VBO and EBO to the buffer memory for OpenGL to use:
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// vertex positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// vertex normals:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	// vertex texture coordinates:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}
