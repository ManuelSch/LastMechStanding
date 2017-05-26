#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 5.0f
#define MOUSE_SENSITIVITY 0.2f
#define JUMP_SPEED 20.0f
#define JUMP_HEIGHT 1.5f

class Player : public SceneObject
{
public:

	Player(Camera* camera, shared_ptr<GUI> gui, GLfloat displayRatio);
	virtual ~Player();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	void movePosition(Movement direction, GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);
	void moveView(GLfloat xOffset, GLfloat yOffset);

	void decreaseHealthPoints(GLfloat damage);

	void jump();

	GLfloat jumpHeight;

private:
	GLfloat movementSpeed, mouseSensitivity;
	GLfloat healthPoints;
	Camera* camera;
	shared_ptr<GUI> gui;
};

#endif