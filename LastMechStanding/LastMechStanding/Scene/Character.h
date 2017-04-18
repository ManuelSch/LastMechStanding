#pragma once

#include "..\commonHeader.h"
#include "SceneObject.h"

#ifdef SCENE_OBJECT

class Character : public SceneObject
{
public:
	Character();
	virtual ~Character();

	virtual void update(float deltaTime);
	virtual void draw(Camera* camera, Display* display);
};

#endif