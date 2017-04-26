#pragma once

#include "..\..\commonHeader.h"
#include "Mesh.h"

class Model
{
public:
	Model(GLchar* path);
	void draw(Shader* shader);
	~Model();
	
private:
	// model data:
	vector<Mesh> meshes;
	string directory;

	vector<Texture> textures_loaded;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, string typeName);
	GLint textureFromFile(const char* path, string directory);
};

