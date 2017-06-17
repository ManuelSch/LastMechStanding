#pragma once

#include "..\commonHeader.h"
#include "..\Scene\LightSource.h"
#include "..\Scene\SceneObjects\SceneObject.h"
#include "..\..\Game\ShortKeys.h"

class ShadowMap
{
public:
	ShadowMap(shared_ptr<LightSource> lightSource);
	~ShadowMap();

	GLuint depthMap;
	glm::mat4 lightSpaceMatrix;

	void renderToDepthMap(vector<shared_ptr<SceneObject>>* sceneObjects, ShortKeys* shortKeys);

private:
	GLuint depthMapFBO;

	shared_ptr<LightSource> lightSource;

	// constants:
	GLfloat near_plane, far_plane;
	GLfloat yOffset;
	GLuint SHADOW_WIDTH, SHADOW_HEIGHT;
	glm::mat4 lightProjection;
};