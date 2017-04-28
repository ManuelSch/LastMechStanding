#pragma once

#include "..\..\commonHeader.h"
#include "..\SceneObject.h"

#ifdef SCENE_OBJECT

class Floor : public SceneObject 
{
public:
	Floor();
	virtual ~Floor();

	virtual void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources);
	virtual void update(float timeDelta);

};

#endif