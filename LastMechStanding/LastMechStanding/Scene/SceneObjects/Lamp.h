#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"

class Lamp : public SceneObject
{
public:
	Lamp();
	virtual ~Lamp();

	virtual void update(GLfloat deltaTime);
};

