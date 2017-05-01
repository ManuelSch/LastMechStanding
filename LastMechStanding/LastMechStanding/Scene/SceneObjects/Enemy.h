#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 5.0f

class Enemy : public SceneObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void update(GLfloat deltaTime);

	virtual void onClick();

	GLfloat healthPoints;

private:
	GLfloat movementSpeed;
	glm::vec3 destination;
	void setNewDestination();
};

#endif