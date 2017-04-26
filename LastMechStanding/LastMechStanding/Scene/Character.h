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
	virtual void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources);
};

#endif