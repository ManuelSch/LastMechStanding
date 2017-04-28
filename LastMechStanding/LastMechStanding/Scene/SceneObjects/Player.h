#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"

#ifdef SCENE_OBJECT

class Player : public SceneObject
{
public:

	Player(Camera* camera);
	virtual ~Player();

	virtual void update(float deltaTime);

	void movePosition(Movement direction, GLfloat deltaTime);
	void moveView(GLfloat xOffset, GLfloat yOffset);

private:
	GLfloat movementSpeed, mouseSensitivity;
	Camera* camera;
};

#endif