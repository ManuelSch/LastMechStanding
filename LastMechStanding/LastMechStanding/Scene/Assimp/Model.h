#pragma once

#include "..\..\commonHeader.h"
#include "Mesh.h"
#include "..\..\Util\BoundingBox.h"
#include "..\..\Game\ShortKeys.h"

class Model
{
public:
	Model();
	Model(GLchar* path);
	void draw(Shader* shader, ShortKeys* shortKeys);
	~Model();

	shared_ptr<BoundingBox> boundingBox;
	
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

