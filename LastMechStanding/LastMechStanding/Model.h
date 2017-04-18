#pragma once

#include "commonHeader.h"
#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
	Model(GLchar* path);
	void Draw(Shader shader);
	~Model();
	
private:
	// model data:
	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLint TextureFromFile(const char* path, std::string directory);
};

