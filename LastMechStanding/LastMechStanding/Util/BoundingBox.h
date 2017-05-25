#pragma once


#include "..\..\commonHeader.h"


class BoundingBox
{
public:
	BoundingBox(glm::vec3 minVertexPos, glm::vec3 maxVertexPos);
	~BoundingBox();

	glm::vec3 minVertexPos, maxVertexPos;

	glm::mat4 getMatrix();

	glm::mat4 transformMatrix;
};

