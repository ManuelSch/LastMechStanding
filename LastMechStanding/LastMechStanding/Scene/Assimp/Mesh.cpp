#include "Mesh.h"


Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, shared_ptr<BoundingBox> boundingBox)
	: vertices(vertices), indices(indices), textures(textures)
{
	glm::vec3 minVertexPos = boundingBox->minVertexPos;
	glm::vec3 maxVertexPos = boundingBox->maxVertexPos;

	for (GLuint i = 0; i < this->vertices.size(); i++)
	{
		boundingBox->minVertexPos.x = min(this->vertices[i].position.x, boundingBox->minVertexPos.x);
		boundingBox->minVertexPos.y = min(this->vertices[i].position.y, boundingBox->minVertexPos.y);
		boundingBox->minVertexPos.z = min(this->vertices[i].position.z, boundingBox->minVertexPos.z);

		boundingBox->maxVertexPos.x = max(this->vertices[i].position.x, boundingBox->maxVertexPos.x);
		boundingBox->maxVertexPos.y = max(this->vertices[i].position.y, boundingBox->maxVertexPos.y);
		boundingBox->maxVertexPos.z = max(this->vertices[i].position.z, boundingBox->maxVertexPos.z);
	}


	this->setupMesh();
}

void Mesh::draw(Shader* shader, ShortKeys* shortKeys)
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

		glUniform1i(shader->getUniformLocation(("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);

		if (lastMMQuality != shortKeys->mipMappingQuality)
		{
			lastMMQuality = shortKeys->mipMappingQuality;

			switch (shortKeys->mipMappingQuality) {
			case ShortKeys::MipMappingQuality::OFF:
				if (shortKeys->textureSamplingQuality == ShortKeys::TextureSamplingQuality::NEAREST_NEIGHBOR) {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
				else {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				}
				break;
			case ShortKeys::MipMappingQuality::NEAREST_NEIGHBOR:
				if (shortKeys->textureSamplingQuality == ShortKeys::TextureSamplingQuality::NEAREST_NEIGHBOR) {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				}
				else {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				}
				break;
			case ShortKeys::MipMappingQuality::LINEAR:
				if (shortKeys->textureSamplingQuality == ShortKeys::TextureSamplingQuality::NEAREST_NEIGHBOR) {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				}
				else {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				}
				break;
			}
		}

		if (shortKeys->textureSamplingQuality == ShortKeys::TextureSamplingQuality::NEAREST_NEIGHBOR) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	// default shininess:
	glUniform1f(shader->getUniformLocation("material.shininess"), 16.0f);

	glActiveTexture(GL_TEXTURE0);

	// draw mesh:
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// set everything back to defaults once configured:
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
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

	// vertex data:
	// positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// normals:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	// texture coordinates:
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}
