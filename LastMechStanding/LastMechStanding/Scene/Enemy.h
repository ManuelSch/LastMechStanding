#pragma once

#include "..\commonHeader.h"
#include "SceneObject.h"
#include "Character.h"

#ifdef SCENE_OBJECT

class Enemy : public SceneObject
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void update(float deltaTime);
	virtual void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources);

	void move(float deltatime);
	void hitEnemy(int damage);

private:

	int health;
	glm::vec3 movedirection;

};

#endif