#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 minVertexPos, glm::vec3 maxVertexPos)
{
	this->minVertexPos = minVertexPos;
	this->maxVertexPos = maxVertexPos;

	glm::vec3 lastPosition = glm::vec3(1234.0f);
	glm::vec3 lastScaling = glm::vec3(1234.0f);
	this->getAllPositions(&glm::vec3(0.0f), &glm::vec3(0.0f));
}


BoundingBox::~BoundingBox()
{
}



vector<glm::vec3> BoundingBox::getAllPositions(glm::vec3* position, glm::vec3* scaling)
{
	if (distance(*position, this->lastPosition) == 0.0f && distance(*scaling, this->lastScaling) == 0.0f) {
		//cout << "cache!!!!" << endl;
		return this->lastAllPositions;
	}
	cout << "no cache!!!!" << endl;
	this->lastPosition = *position;
	this->lastScaling = *scaling;

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
	
	GLfloat interval = 2.0f;
	for (GLfloat z = bbSelfMin.z; z <= bbSelfMax.z; z += interval) {
		for (GLfloat y = bbSelfMin.y; y <= bbSelfMax.y; y += interval) {
			for (GLfloat x = bbSelfMin.x; x <= bbSelfMax.x; x += interval) {
				result.push_back(glm::vec3(x, y, z));
			}
		}
	}
	/*
	for (GLfloat z = min(bbSelfMin.z, bbSelfMax.z); z <= max(bbSelfMin.z, bbSelfMax.z); z += interval) {
		for (GLfloat y = min(bbSelfMin.y, bbSelfMax.y); y <= max(bbSelfMin.y, bbSelfMax.y); y += interval) {
			for (GLfloat x = min(bbSelfMin.x, bbSelfMax.x); x <= max(bbSelfMin.x, bbSelfMax.x); x += interval) {
				result.push_back(glm::vec3(x, y, z));
			}
		}
	}*/

	this->lastAllPositions = result;
	return result;
}

vector<vector<glm::vec3>> BoundingBox::getAllLines(glm::vec3 * position, glm::vec3 * scaling)
{
	vector<glm::vec3> points = this->getAllPositions(position, scaling);

	vector<vector<glm::vec3>> result = vector<vector<glm::vec3>>();
	vector<glm::vec3> line = vector<glm::vec3>();

	line = vector<glm::vec3>();
	line.push_back(points[0]);
	line.push_back(points[1]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[1]);
	line.push_back(points[2]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[2]);
	line.push_back(points[3]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[3]);
	line.push_back(points[0]);
	result.push_back(line);


	line = vector<glm::vec3>();
	line.push_back(points[4]);
	line.push_back(points[5]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[5]);
	line.push_back(points[6]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[6]);
	line.push_back(points[7]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[7]);
	line.push_back(points[4]);
	result.push_back(line);


	line = vector<glm::vec3>();
	line.push_back(points[0]);
	line.push_back(points[4]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[1]);
	line.push_back(points[5]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[2]);
	line.push_back(points[6]);
	result.push_back(line);

	line = vector<glm::vec3>();
	line.push_back(points[3]);
	line.push_back(points[7]);
	result.push_back(line);

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