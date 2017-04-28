#pragma once

#include "..\..\commonHeader.h"
#include ".\SceneObject.h"

#ifdef MAP

class Arena : public SceneObject
{
public:
	Arena();
	~Arena();

	virtual void update(float deltaTime);
};

#endif

