#pragma once

#include "..\..\commonHeader.h"
#include "Map.h"

#ifdef MAP

class Floor : public Map
{
public:
	Floor();
	virtual ~Floor();

	virtual void update(float deltaTime);
	virtual void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources);
	
};

#endif