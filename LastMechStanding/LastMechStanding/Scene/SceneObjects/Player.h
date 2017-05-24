#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 5.0f
#define MOUSE_SENSITIVITY 0.2f

class Player : public SceneObject
{
public:

	Player(Camera* camera, shared_ptr<GUI> gui, GLfloat displayRatio);
	virtual ~Player();

	virtual void update(GLfloat deltaTime);

	void movePosition(Movement direction, GLfloat deltaTime);
	void moveView(GLfloat xOffset, GLfloat yOffset);

	void decreaseHealthPoints(GLfloat damage);

private:
	GLfloat movementSpeed, mouseSensitivity;
	GLfloat healthPoints;
	Camera* camera;
	shared_ptr<GUI> gui;
};

#endif