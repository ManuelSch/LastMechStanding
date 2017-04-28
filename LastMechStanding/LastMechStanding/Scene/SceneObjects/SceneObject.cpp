#include "SceneObject.h"



SceneObject::SceneObject() : model("Resources/Models/Nanosuit/nanosuit.obj")
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::translate(glm::vec3 transformation)
{
	this->modelMatrix = glm::translate(this->modelMatrix, transformation);
}

void SceneObject::rotate(GLfloat angle, glm::vec3 transformation)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(angle), transformation);
}

void SceneObject::scale(glm::vec3 transformation)
{
	this->modelMatrix = glm::scale(this->modelMatrix, transformation);
}

