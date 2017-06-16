#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 minVertexPos, glm::vec3 maxVertexPos)
{
	this->minVertexPos = minVertexPos;
	this->maxVertexPos = maxVertexPos;
}


BoundingBox::~BoundingBox()
{
}



vector<glm::vec3> BoundingBox::getAllPositions(glm::vec3* position, glm::vec3* scaling)
{
	vector<glm::vec3> result = vector<glm::vec3>();

	glm::vec3 bbSelfMin = this->getMinVertexPos(position, scaling);
	glm::vec3 bbSelfMax = this->getMaxVertexPos(position, scaling);

	result.push_back(glm::vec3(bbSelfMin));
	result.push_back(glm::vec3(bbSelfMin.x, bbSelfMin.y, bbSelfMax.z));
	result.push_back(glm::vec3(bbSelfMax.x, bbSelfMin.y, bbSelfMax.z));
	result.push_back(glm::vec3(bbSelfMax.x, bbSelfMin.y, bbSelfMin.z));

	result.push_back(glm::vec3(bbSelfMin.x, bbSelfMax.y, bbSelfMin.z));
	result.push_back(glm::vec3(bbSelfMin.x, bbSelfMax.y, bbSelfMax.z));
	result.push_back(glm::vec3(bbSelfMax));
	result.push_back(glm::vec3(bbSelfMax.x, bbSelfMax.y, bbSelfMin.z));

	return result;
}

glm::vec3 BoundingBox::getMinVertexPos(glm::vec3* position, glm::vec3* scaling)
{
	glm::vec3 result = this->minVertexPos;

	result *= *scaling;

	result += *position;

	return result;
}

glm::vec3 BoundingBox::getMaxVertexPos(glm::vec3* position, glm::vec3* scaling)
{
	glm::vec3 result = this->maxVertexPos;

	result *= *scaling;

	result += *position;

	return result;
}


/*glm::mat4 BoundingBox::getMatrix()
{
	glm::vec3 size = glm::vec3(maxVertexPos.x - minVertexPos.x, maxVertexPos.y - minVertexPos.y, maxVertexPos.z - minVertexPos.z);
	glm::vec3 center = glm::vec3((minVertexPos.x + maxVertexPos.x) / 2, (minVertexPos.y + maxVertexPos.y) / 2, (minVertexPos.z + maxVertexPos.z) / 2);
	glm::mat4 transform = glm::scale(glm::mat4(1), size) * glm::translate(glm::mat4(1), center);

	return transform;
}
*/