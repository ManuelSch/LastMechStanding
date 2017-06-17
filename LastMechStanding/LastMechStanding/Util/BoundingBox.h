#pragma once


#include "..\..\commonHeader.h"


class BoundingBox
{
public:
	BoundingBox(glm::vec3 minVertexPos, glm::vec3 maxVertexPos);
	~BoundingBox();

	glm::vec3 minVertexPos, maxVertexPos;

	vector<glm::vec3> getAllPositions(glm::vec3* position, glm::vec3* scaling, glm::vec3* viewerPos, glm::mat4* projMat, GLfloat angleY);

	void buildCache();
	void buildCache2();

	GLfloat calculateAngle(GLfloat x, GLfloat z, GLfloat xDest, GLfloat zDest);

	glm::vec3 getMinVertexPos(glm::vec3* position, glm::vec3* scaling);
	glm::vec3 getMaxVertexPos(glm::vec3* position, glm::vec3* scaling);

	glm::vec3 lastPosition;
	glm::vec3 lastScaling;
	vector<glm::vec3> lastAllPositions;
	vector<glm::vec3> lastAllPositions2;
};

