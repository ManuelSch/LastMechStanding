#pragma once

#include "..\commonHeader.h"
#include "..\Util\Shader.h"
#include "..\Scene\Camera.h"
#include "..\Game\Display.h"
#include ".\Assimp\Model.h"
#include "..\Scene\LightSource.h"

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	unique_ptr<Shader> shader;
	Model model;
	glm::mat4 modelMatrix;

	virtual void draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources) = 0;
	virtual void update(float timeDelta) = 0;

	void translate(glm::vec3 transformation);
	void rotate(GLfloat angle, glm::vec3 transformation);
	void scale(glm::vec3 transformation);
};

#define SCENE_OBJECT
