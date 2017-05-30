#pragma once

#include "..\..\commonHeader.h"
#include "..\SceneObject.h"

#ifdef SCENE_OBJECT

class Container1 : public SceneObject
{
public:
	Container1(glm::vec3 position);
	~Container1();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);
};

#endif