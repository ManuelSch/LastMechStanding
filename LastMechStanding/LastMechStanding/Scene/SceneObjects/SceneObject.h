#pragma once

#ifndef SCENE_OBJECT
#define SCENE_OBJECT

#include "..\..\commonHeader.h"
#include "..\..\Util\Shader.h"
#include "..\Camera.h"
#include "..\..\Game\Display.h"
#include ".\..\Assimp\Model.h"
#include "..\..\Scene\LightSource.h"

#define JUMP_SPEED 20.0f
#define JUMP_HEIGHT 1.5f

class SceneObject
{
public:
	GLboolean dead = false;
	const GLfloat objectID = rand() + glfwGetTime();

	SceneObject();
	virtual ~SceneObject();

	void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources, glm::mat4* lightSpaceMatrix, GLuint* depthMap);
	void drawPicking(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, GLuint pickingID);
	void drawDepthMap(glm::mat4* lightSpaceMatrix);
	virtual void update(GLfloat timeDelta, vector<shared_ptr<SceneObject>>* sceneObjects) = 0;

	virtual void onClick();

	void translate(glm::vec3 transformation, vector<shared_ptr<SceneObject>>* sceneObjects);
	void rotate(GLfloat angle, glm::vec3 transformation);
	void scale(glm::vec3 transformation);

	void moveTowards(glm::vec3 target, GLfloat distance, vector<shared_ptr<SceneObject>>* sceneObjects);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), angle = glm::vec3(0.0f, 0.0f, 0.0f), scaling = glm::vec3(1.0f, 1.0f, 1.0f);
	Model model;
	glm::mat4 getModelMatrix();
	GLboolean isJumping = false;
	GLfloat jumpHeight;
	GLboolean canJump = true;

	void jump();


	void printPosition();
	static glm::vec3 getRandomPosition(GLfloat yDefault = 0.0f);

protected:
	shared_ptr<Shader> shader;
	shared_ptr<Shader> pickingShader;
	shared_ptr<Shader> simpleDepthShader;



	GLfloat calculateAngle(GLfloat x, GLfloat y, GLfloat xDest, GLfloat yDest);
	GLboolean intersectsWith(shared_ptr<SceneObject> other);
};


#endif
