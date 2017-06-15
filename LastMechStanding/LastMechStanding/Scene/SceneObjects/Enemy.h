#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "EnemyTop.h"
#include "Player.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 5.0f

class Enemy : public SceneObject
{
public:
	Enemy(shared_ptr<GUI> gui, shared_ptr<Player> player);
	virtual ~Enemy();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	virtual void onClick();

	GLfloat healthPoints;

	GLfloat movementSpeed;
	shared_ptr<GUI> gui;
	shared_ptr<Player> player;

	glm::vec3 lastPosition;
	GLfloat timeStandingStill;

	void reset();

	void setNewDestination();
};

#endif