#pragma once

#include "..\..\commonHeader.h"
#include "SceneObject.h"

#ifdef SCENE_OBJECT

class Player : public SceneObject
{
public:
	enum MovementDirection {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	Player();
	virtual ~Player();

	virtual void update(float deltaTime);
	virtual void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources);
	virtual void drawPicking(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, GLuint pickingID);

	void Player::move(MovementDirection direction, GLfloat deltaTime);

private:
	GLfloat movementSpeed;
};

#endif