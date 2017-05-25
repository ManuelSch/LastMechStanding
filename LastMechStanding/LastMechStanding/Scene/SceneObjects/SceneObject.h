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

	SceneObject();
	virtual ~SceneObject();

	void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources, glm::mat4* lightSpaceMatrix, GLuint* depthMap);
	void drawPicking(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, GLuint pickingID);
	void drawDepthMap(glm::mat4* lightSpaceMatrix);
	virtual void update(GLfloat timeDelta) = 0;

	virtual void onClick();

	void translate(glm::vec3 transformation);
	void rotate(GLfloat angle, glm::vec3 transformation);
	void scale(glm::vec3 transformation);

	void moveTowards(glm::vec3 target, GLfloat distance);

	glm::vec3 position, angle, scaling;
	Model model;
	void asdf();
	glm::mat4 getModelMatrix();
protected:
	shared_ptr<Shader> shader;
	shared_ptr<Shader> pickingShader;
	shared_ptr<Shader> simpleDepthShader;



	GLfloat calculateAngle(GLfloat x, GLfloat y, GLfloat xDest, GLfloat yDest);
};


#endif
