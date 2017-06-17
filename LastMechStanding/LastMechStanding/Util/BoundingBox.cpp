#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 minVertexPos, glm::vec3 maxVertexPos)
{
	this->minVertexPos = minVertexPos;
	this->maxVertexPos = maxVertexPos;
	/*
	lastPosition = glm::vec3(1234.0f);
	lastScaling = glm::vec3(1234.0f);
	this->getAllPositions(&glm::vec3(0.0f), &glm::vec3(0.0f), &minVertexPos, nullptr, 0.0f);
	lastPosition = glm::vec3(-1234.0f);
	lastScaling = glm::vec3(-1234.0f);
	this->getAllPositions(&glm::vec3(1000.0f), &glm::vec3(1000.0f), &glm::vec3(1000.0f), nullptr, 0.0f);*/
}


BoundingBox::~BoundingBox()
{
}



vector<glm::vec3> BoundingBox::getAllPositions(glm::vec3* position, glm::vec3* scaling, glm::vec3* viewerPos, glm::mat4* projMat, GLfloat angleY)
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


	glm::vec4 Pclip;
	GLboolean cull = true;

	GLfloat minDist = 1000.0f;
	for (GLuint i = 0; i < result.size(); i++) {
		minDist = min(distance(result[i], *viewerPos), minDist);

		if (projMat != nullptr) {
			Pclip = (*projMat) * glm::vec4(result[i], 1.0f);
			if (abs(Pclip.x) < Pclip.w && abs(Pclip.y) < Pclip.w && 0 < Pclip.z && Pclip.z < Pclip.w) {
				return vector<glm::vec3>();
			}

			GLfloat angleBetween = calculateAngle(result[i].x, result[i].z, viewerPos->x, viewerPos->z);
			angleBetween += (360 - angleY);
			while (angleBetween >= 360.0f) {
				angleBetween -= 360.0f;
			}
			if (angleBetween >(90 + 20 - 20) && angleBetween < (270 - 20 + 20)) {
				cull = false;
			}
		}
	}
	if (projMat != nullptr && cull) {
		result = vector<glm::vec3>();
		result.push_back(glm::vec3());
		return result;
	}
	

	if (minDist <= 60.0f) {
		if (!this->lastAllPositions.empty() && distance(*position, this->lastPosition) == 0.0f && distance(*scaling, this->lastScaling) == 0.0f) {
			//cout << "cache!!!!" << endl;
			return this->lastAllPositions;
		}

		GLfloat interval = 2.0f;
		for (GLfloat z = bbSelfMin.z - 1.0f; z <= bbSelfMax.z + 1.0f; z += interval) {
			for (GLfloat y = bbSelfMin.y - 1.0f; y <= bbSelfMax.y + 1.0f; y += interval) {
				for (GLfloat x = bbSelfMin.x - 1.0f; x <= bbSelfMax.x + 1.0f; x += interval) {
					result.push_back(glm::vec3(x, y, z));
					
					if (projMat != nullptr) {
						Pclip = (*projMat) * glm::vec4(glm::vec3(x, y, z), 1.0f);
						if (abs(Pclip.x) < Pclip.w && abs(Pclip.y) < Pclip.w && 0 < Pclip.z && Pclip.z < Pclip.w) {
							return vector<glm::vec3>();
						}
					}
				}
			}
		}
		this->lastAllPositions = result;
	}
	else {
		if (!this->lastAllPositions2.empty() && distance(*position, this->lastPosition) == 0.0f && distance(*scaling, this->lastScaling) == 0.0f) {
			//cout << "cache!!!!" << endl;
			return this->lastAllPositions2;
		}

		GLfloat interval = 2.0f;
		for (GLfloat z = bbSelfMin.z - 1.0f; z <= bbSelfMax.z + 1.0f; z += interval) {
			for (GLfloat y = bbSelfMin.y - 1.0f; y <= bbSelfMax.y + 1.0f; y += interval) {
				for (GLfloat x = bbSelfMin.x - 1.0f; x <= bbSelfMax.x + 1.0f; x += interval) {
					result.push_back(glm::vec3(x, y, z));

					if (projMat != nullptr) {
						Pclip = (*projMat) * glm::vec4(glm::vec3(x, y, z), 1.0f);
						if (abs(Pclip.x) < Pclip.w && abs(Pclip.y) < Pclip.w && 0 < Pclip.z && Pclip.z < Pclip.w) {
							return vector<glm::vec3>();
						}
					}
				}
			}
		}
		this->lastAllPositions2 = result;
	}

	cout << "no cache!!!!" << endl;
	this->lastPosition = *position;
	this->lastScaling = *scaling;

	/*
	for (GLfloat z = min(bbSelfMin.z, bbSelfMax.z); z <= max(bbSelfMin.z, bbSelfMax.z); z += interval) {
		for (GLfloat y = min(bbSelfMin.y, bbSelfMax.y); y <= max(bbSelfMin.y, bbSelfMax.y); y += interval) {
			for (GLfloat x = min(bbSelfMin.x, bbSelfMax.x); x <= max(bbSelfMin.x, bbSelfMax.x); x += interval) {
				result.push_back(glm::vec3(x, y, z));
			}
		}
	}*/

	return result;
}

void BoundingBox::buildCache()
{
}

void BoundingBox::buildCache2()
{
}

GLfloat BoundingBox::calculateAngle(GLfloat x, GLfloat z, GLfloat xDest, GLfloat zDest)
{
	GLfloat deltaZ = abs(zDest - z);
	GLfloat deltaX = abs(xDest - x);

	if (xDest >= x) {
		if (zDest >= z) {
			return (float)glm::degrees(2 * M_PI - atan(deltaZ / deltaX));
		}
		else {
			return (float)glm::degrees(atan(deltaZ / deltaX));
		}
	}
	else {
		if (zDest >= z) {
			return (float)glm::degrees(M_PI + atan(deltaZ / deltaX));
		}
		else {
			return (float)glm::degrees(M_PI - atan(deltaZ / deltaX));
		}
	}
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