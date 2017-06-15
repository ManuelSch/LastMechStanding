#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "BulletPlayer.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 8.0f//!--20.0f
#define MOUSE_SENSITIVITY 0.2f

class Player : public SceneObject
{
public:

	Player(Camera* camera, shared_ptr<GUI> gui, GLfloat displayRatio);
	virtual ~Player();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	void movePosition(Movement direction, GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);
	void moveView(GLfloat xOffset, GLfloat yOffset);

	void decreaseHealthPoints(GLfloat damage);

	vector<shared_ptr<BulletPlayer>> bullets;
	GLfloat shootTimer = 0.0f;

	void shoot();

	GLfloat movementSpeed, mouseSensitivity;
	GLfloat healthPoints;
	Camera* camera;
	shared_ptr<GUI> gui;
	GLboolean shootLeft = false;
};

#endif