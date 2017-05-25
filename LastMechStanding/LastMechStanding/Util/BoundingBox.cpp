#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 minVertexPos, glm::vec3 maxVertexPos)
{
	this->minVertexPos = minVertexPos;
	this->maxVertexPos = maxVertexPos;
}


BoundingBox::~BoundingBox()
{
}

glm::mat4 BoundingBox::getMatrix()
{
	glm::vec3 size = glm::vec3(maxVertexPos.x - minVertexPos.x, maxVertexPos.y - minVertexPos.y, maxVertexPos.z - minVertexPos.z);
	glm::vec3 center = glm::vec3((minVertexPos.x + maxVertexPos.x) / 2, (minVertexPos.y + maxVertexPos.y) / 2, (minVertexPos.z + maxVertexPos.z) / 2);
	glm::mat4 transform = glm::scale(glm::mat4(1), size) * glm::translate(glm::mat4(1), center);

	return transform;
}
