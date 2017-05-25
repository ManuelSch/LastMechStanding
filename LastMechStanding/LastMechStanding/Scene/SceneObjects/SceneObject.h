#pragma once

#ifndef SCENE_OBJECT
#define SCENE_OBJECT

#include "..\..\commonHeader.h"
#include "..\..\Util\Shader.h"
#include "..\Camera.h"
#include "..\..\Game\Display.h"
#include ".\..\Assimp\Model.h"
#include "..\..\Scene\LightSource.h"

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

	glm::vec3 position, angle, scaling;
	Model model;
	glm::mat4 getModelMatrix();
	GLboolean isJumping = false;
	GLboolean canJump = true;
protected:
	shared_ptr<Shader> shader;
	shared_ptr<Shader> pickingShader;
	shared_ptr<Shader> simpleDepthShader;



	GLfloat calculateAngle(GLfloat x, GLfloat y, GLfloat xDest, GLfloat yDest);
	GLboolean intersectsWith(shared_ptr<SceneObject> other);
};


#endif
