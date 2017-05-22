#pragma once

#include "..\..\commonHeader.h"
#include "..\Assimp/Model.h"
#include "SceneObject.h"
#include "Player.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 5.0f

class Enemy : public SceneObject
{
public:
	Enemy(shared_ptr<GUI> gui);
	virtual ~Enemy();

	virtual void update(GLfloat deltaTime);

	virtual void onClick();

	GLfloat healthPoints;

	//Bounding Box
	glm::vec3 maxBBspawn;
	glm::vec3 minBBspawn;
	glm::vec3 maxBB;
	glm::vec3 minBB;

	bool collidesWithEnemy(Enemy* enemy);

private:
	GLfloat movementSpeed;
	glm::vec3 destination;
	shared_ptr<GUI> gui;

	void setNewDestination();
};

#endif