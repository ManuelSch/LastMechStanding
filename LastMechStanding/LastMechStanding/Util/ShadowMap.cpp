#include "ShadowMap.h"



ShadowMap::ShadowMap(shared_ptr<LightSource> lightSource)
{
	// set constants:
	near_plane = 0.1f;
	far_plane = 50.0f;
	yOffset = 17.0f;
	SHADOW_WIDTH = 1024 * 10;
	SHADOW_HEIGHT = SHADOW_WIDTH;
	lightProjection = glm::ortho(-170.0f, 170.0f, -170.0f, 170.0f, near_plane, far_plane);

	this->lightSource = lightSource;

	// framebuffer for rendering the depth map:
	glGenFramebuffers(1, &depthMapFBO);

	// framebuffer's depth buffer texture:
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// prevent the areas outside the depth map projection to be dark:
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach it as the framebuffer's depth buffer:
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

	// tell OpenGL explicitly that there is no color buffer:
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::renderToDepthMap(vector<shared_ptr<SceneObject>>* sceneObjects, ShortKeys* shortKeys)
{
	// view matrix for the sunlight:
	glm::mat4 lightView = glm::lookAt(glm::vec3(lightSource->position.x, lightSource->position.y + yOffset, lightSource->position.z), glm::vec3(lightSource->position.x, lightSource->position.y + yOffset, lightSource->position.z) + lightSource->direction, glm::vec3(0.0, 1.0, 0.0));
	//glm::mat4 lightView = glm::lookAt(sunLight->position, sunLight->position + sunLight->direction, glm::vec3(0.0, 1.0, 0.0));
	
	// light space matrix for the sunlight:
	lightSpaceMatrix = lightProjection * lightView;
	
	// prevent "peter panning" by culling the front faces:
	//glCullFace(GL_FRONT);
	
	// draw objects:
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	for (GLuint i = 0; i < sceneObjects->size(); i++) {
		if ((*sceneObjects)[i] != nullptr) {
			(*sceneObjects)[i]->drawDepthMap(&lightSpaceMatrix, shortKeys);
		}
	}
	
	// set culling back to default:
	//glCullFace(GL_BACK);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}