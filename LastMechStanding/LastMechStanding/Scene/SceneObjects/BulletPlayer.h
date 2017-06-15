#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

class BulletPlayer : public SceneObject
{
public:
	BulletPlayer(SceneObject* parent);
	virtual ~BulletPlayer();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	virtual void onClick();

	void shoot(glm::vec3 shootTowards, glm::vec3 offsetPosition);

	GLfloat movementSpeed = 100.0f;

private:

	glm::vec3 direction;
};

#endif

