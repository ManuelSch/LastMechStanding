#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

#define HEALTH_POINTS_MAX 100.0f
#define MOVEMENT_SPEED 5.0f

class EnemyTop : public SceneObject
{
public:
	EnemyTop(SceneObject* parent);
	virtual ~EnemyTop();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	virtual void onClick();

private:
	SceneObject* parent;
};

#endif