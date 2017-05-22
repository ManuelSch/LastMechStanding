#pragma once

#include "..\..\commonHeader.h"
#include ".\SceneObject.h"

#ifdef SCENE_OBJECT

class Arena : public SceneObject
{
public:
	Arena();
	~Arena();

	virtual void update(GLfloat deltaTime);

	
};

#endif

