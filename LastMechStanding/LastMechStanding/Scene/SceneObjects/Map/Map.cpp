#include "Map.h"



Map::Map() : model("Resources/Models/Nanosuit/nanosuit.obj")
{
}


Map::~Map()
{
}

void Map::translate(glm::vec3 transformation)
{
	this->modelMatrix = glm::translate(this->modelMatrix, transformation);
}

void Map::rotate(GLfloat angle, glm::vec3 transformation)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), transformation);
}

void Map::scale(glm::vec3 transformation)
{
	this->modelMatrix = glm::scale(this->modelMatrix, transformation);
}

