#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"
#include "Player.h"
#include "Bullet.h"
#include "..\GUI.h"

#ifdef SCENE_OBJECT

class EnemyTop : public SceneObject
{
public:
	EnemyTop(SceneObject* parent, shared_ptr<Player> player);
	virtual ~EnemyTop();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);

	virtual void onClick();

	shared_ptr<Player> player;

	vector<shared_ptr<Bullet>> bullets;

	GLfloat shootTimer = 0.0f;
};

#endif