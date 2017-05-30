#pragma once

#include "..\..\commonHeader.h"
#include "..\SceneObject.h"

#ifdef SCENE_OBJECT

class ArenaWall : public SceneObject
{
public:
	ArenaWall(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), GLboolean rotated = false);
	~ArenaWall();

	virtual void update(GLfloat deltaTime, vector<shared_ptr<SceneObject>>* sceneObjects);
};

#endif

