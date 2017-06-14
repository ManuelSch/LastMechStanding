#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "Player.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

class Bullet : public SceneObject
{
public:
	Bullet(SceneObject* parent);
	virtual ~Bullet();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	virtual void onClick();

	void shoot(glm::vec3 shootTowards);

	GLfloat movementSpeed = 300.0f;


private:
	SceneObject* parent;

	//GLboolean asdf = true;

	glm::vec3 direction;
};

#endif

