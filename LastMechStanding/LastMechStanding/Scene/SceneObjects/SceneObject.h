#pragma once

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

	void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources);
	void drawPicking(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, GLuint pickingID);
	virtual void update(GLfloat timeDelta) = 0;

	virtual void onClick();

	void translate(glm::vec3 transformation);
	void rotate(GLfloat angle, glm::vec3 transformation);
	void scale(glm::vec3 transformation);

	void moveTowards(glm::vec3 target, GLfloat distance);

protected:
	unique_ptr<Shader> shader;
	unique_ptr<Shader> pickingShader;
	Model model;

	glm::vec3 position, angle, scaling;

	glm::mat4 getModelMatrix();

	GLfloat calculateAngle(GLfloat x, GLfloat y, GLfloat xDest, GLfloat yDest);
};

#define SCENE_OBJECT
