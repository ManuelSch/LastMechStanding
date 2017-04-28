#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"

#ifdef SCENE_OBJECT

class Enemy : public SceneObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void update(float deltaTime);
};

#endif