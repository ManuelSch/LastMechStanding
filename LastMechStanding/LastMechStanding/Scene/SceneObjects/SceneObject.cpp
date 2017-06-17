#include "SceneObject.h"


SceneObject::SceneObject() : model(), position(0.0f), angle(0.0f), scaling(1.0f)
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources, ShortKeys* shortKeys, glm::mat4* lightSpaceMatrix, GLuint* depthMap)
{
	if (!this->visible) {
		return;
	}

	shader->useShader();

	// send light parameters to the shader:
	for (GLuint i = 0; i < lightSources->size(); i++)
	{
		if ((*lightSources)[i]->type == LightSource::DIRECTIONAL) {
			glUniform3f(shader->getUniformLocation("dirLight.direction"), (*lightSources)[i]->direction.x, (*lightSources)[i]->direction.y, (*lightSources)[i]->direction.z);
			glUniform3f(shader->getUniformLocation("dirLight.ambient"), (*lightSources)[i]->ambient.x, (*lightSources)[i]->ambient.y, (*lightSources)[i]->ambient.z);
			glUniform3f(shader->getUniformLocation("dirLight.diffuse"), (*lightSources)[i]->diffuse.x, (*lightSources)[i]->diffuse.y, (*lightSources)[i]->diffuse.z);
			glUniform3f(shader->getUniformLocation("dirLight.specular"), (*lightSources)[i]->specular.x, (*lightSources)[i]->specular.y, (*lightSources)[i]->specular.z);
		}
		else if ((*lightSources)[i]->type == LightSource::POINT) {
			// TODO
		}
	}

	if (lightSpaceMatrix != nullptr && depthMap != nullptr) {
		glUniformMatrix4fv(shader->getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(*lightSpaceMatrix));
		glUniform1i(shader->getUniformLocation("shadowMap"), 10);
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, *depthMap);
	}
	else {
		glUniform1i(shader->getUniformLocation("shadowMap"), 10);
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// send viewer position to the shader:
	glUniform3f(shader->getUniformLocation("viewPos"), camera->position.x, camera->position.y, camera->position.z);

	// apply view and projection matrices:
	glUniformMatrix4fv(shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(*projectionMatrix));

	// draw the loaded model:
	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(getModelMatrix()));

	this->model.draw(shader.get(), shortKeys);

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->draw(viewMatrix, projectionMatrix, camera, lightSources, shortKeys, lightSpaceMatrix, depthMap);
	}
}

void SceneObject::drawPicking(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, GLuint pickingID, ShortKeys* shortKeys)
{
	if (!this->collide) {
		return;
	}

	if (pickingShader == nullptr) {
		return;
	}

	pickingShader->useShader();

	// calculate picking ID of the object:
	GLint r = (pickingID & 0x000000FF) >> 0;
	GLint g = (pickingID & 0x0000FF00) >> 8;
	GLint b = (pickingID & 0x00FF0000) >> 16;
	glUniform4f(pickingShader->getUniformLocation("pickingColor"), r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

	// send viewer position to the shader:
	glUniform3f(pickingShader->getUniformLocation("viewPos"), camera->position.x, camera->position.y, camera->position.z);

	// apply view and projection matrices:
	glUniformMatrix4fv(pickingShader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(pickingShader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(*projectionMatrix));


	// draw the loaded model:
	glUniformMatrix4fv(pickingShader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
	this->model.draw(pickingShader.get(), shortKeys);

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		if (this->children[j]->collide) {
			this->children[j]->drawPicking(viewMatrix, projectionMatrix, camera, pickingID, shortKeys);
		}
	}
}

void SceneObject::drawDepthMap(glm::mat4* lightSpaceMatrix, ShortKeys* shortKeys)
{
	if (!this->visible) {
		return;
	}

	if (simpleDepthShader == nullptr) {
		return;
	}

	simpleDepthShader->useShader();

	glUniformMatrix4fv(simpleDepthShader->getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(*lightSpaceMatrix));

	// draw the loaded model:
	glUniformMatrix4fv(simpleDepthShader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
	this->model.draw(simpleDepthShader.get(), shortKeys);

	// children:
	for (GLuint j = 0; j < this->children.size(); j++) {
		this->children[j]->drawDepthMap(lightSpaceMatrix, shortKeys);
	}
}

void SceneObject::translate(glm::vec3 transformation, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	glm::vec3 tempPos = glm::vec3(this->position.x, this->position.y, this->position.z);
	GLboolean intersects;

	this->position.y += transformation.y;

	this->position.x += transformation.x;
	intersects = false;
	for (GLuint i = 0; i < sceneObjects->size(); i++) {
		if ((*sceneObjects)[i]->objectID != this->objectID) {
			if (this->intersectsWith((*sceneObjects)[i])) {
				intersects = true;
				break;
			}
		}
	}
	if (intersects) {
		this->position.x = tempPos.x;
		this->position.y = tempPos.y;
	}

	this->position.z += transformation.z;
	intersects = false;
	for (GLuint i = 0; i < sceneObjects->size(); i++) {
		if ((*sceneObjects)[i]->objectID != this->objectID) {
			if (this->intersectsWith((*sceneObjects)[i])) {
				intersects = true;
				break;
			}
		}
	}
	if (intersects) {
		this->position.z = tempPos.z;
		this->position.y = tempPos.y;
	}
}

void SceneObject::rotate(GLfloat angle, glm::vec3 transformation)
{
	this->angle += transformation * angle;
}

void SceneObject::scale(glm::vec3 transformation)
{
	this->scaling *= transformation;
}

void SceneObject::moveTowards(glm::vec3 target, GLfloat distance, vector<shared_ptr<SceneObject>>* sceneObjects)
{
	GLfloat direction = calculateAngle(position.x, position.z, target.x, target.z);

	GLfloat moveX = (GLfloat)cos(glm::radians(direction)) * distance;
	GLfloat moveZ = -(GLfloat)sin(glm::radians(direction)) * distance;

	translate(glm::vec3(moveX, 0.0f, moveZ), sceneObjects);
	this->angle.y = direction;
}

void SceneObject::onClick()
{
}

glm::mat4 SceneObject::getModelMatrix()
{
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scaling);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));

	while (angle.x >= 360.0f) {
		angle.x -= 360.0f;
	}
	while (angle.y >= 360.0f) {
		angle.y -= 360.0f;
	}
	while (angle.z >= 360.0f) {
		angle.z -= 360.0f;
	}

	return modelMatrix;
}

void SceneObject::jump()
{
	if (canJump) {
		jumpHeight = JUMP_HEIGHT;
		canJump = false;
		isJumping = true;
	}
}

void SceneObject::printPosition()
{
	printf("%0.2f, %0.2f, %0.2f\n", position.x, position.y, position.z);
}

glm::vec3 SceneObject::getRandomPosition(GLfloat yDefault)
{
	return glm::vec3((GLfloat)((double)rand() / (double)RAND_MAX) * 80.0f - 4.0f, yDefault, (GLfloat)((double)rand() / (double)RAND_MAX) * 80.0f - 40.0f);
}

GLboolean SceneObject::isInFrustum(glm::mat4* projMat, Camera* camera, SceneObject* player)
{
	vector<glm::vec3> bbPoints = this->model.boundingBox->getAllPositions(&(this->position), &(this->scaling), &(player->position), projMat, player->angle.y);

	if (bbPoints.size() == 0) {
		return true;
	}
	if (bbPoints.size() == 1) {
		return false;
	}

	GLboolean cull = true;
	for (GLuint i = 0; i < 8; i++) {
		GLfloat angleBetween = calculateAngle(bbPoints[i].x, bbPoints[i].z, player->position.x, player->position.z);
		angleBetween += (360 - player->angle.y);
		while (angleBetween >= 360.0f) {
			angleBetween -= 360.0f;
		}
		if (angleBetween > (90+20-20) && angleBetween < (270-20+20)) {
			cull = false;
		}
	}
	if (cull) {
		return false;
	}

	glm::vec4 Pclip;
	for (GLuint i = 0; i < bbPoints.size(); i++) {
		Pclip = (*projMat) * glm::vec4(bbPoints[i], 1.0f);
		if (abs(Pclip.x) < Pclip.w && abs(Pclip.y) < Pclip.w && 0 < Pclip.z && Pclip.z < Pclip.w) {
			return true;
		}
	}

	return false;
}

GLfloat SceneObject::calculateAngle(GLfloat x, GLfloat z, GLfloat xDest, GLfloat zDest)
{
	GLfloat deltaZ = abs(zDest - z);
	GLfloat deltaX = abs(xDest - x);

	if (xDest >= x) {
		if (zDest >= z) {
			return (float)glm::degrees(2 * M_PI - atan(deltaZ / deltaX));
		}
		else {
			return (float)glm::degrees(atan(deltaZ / deltaX));
		}
	}
	else {
		if (zDest >= z) {
			return (float)glm::degrees(M_PI + atan(deltaZ / deltaX));
		}
		else {
			return (float)glm::degrees(M_PI - atan(deltaZ / deltaX));
		}
	}
}

GLboolean SceneObject::intersectsWith(shared_ptr<SceneObject> other)
{
	if (!other->collide) {
		return false;
	}

	if (distance(this->position, other->position) > 500.0f) {
		return false;
	}
	glm::vec3 bbSelfMin = this->model.boundingBox->getMinVertexPos(&(this->position), &(this->scaling));
	glm::vec3 bbSelfMax = this->model.boundingBox->getMaxVertexPos(&(this->position), &(this->scaling));
	glm::vec3 bbOtherMin = other->model.boundingBox->getMinVertexPos(&(other->position), &(other->scaling));
	glm::vec3 bbOtherMax = other->model.boundingBox->getMaxVertexPos(&(other->position), &(other->scaling));

	GLboolean result = ((bbSelfMin.x <= bbOtherMax.x && bbSelfMax.x >= bbOtherMin.x) &&
						(bbSelfMin.y <= bbOtherMax.y && bbSelfMax.y >= bbOtherMin.y) &&
						(bbSelfMin.z <= bbOtherMax.z && bbSelfMax.z >= bbOtherMin.z));

	GLboolean hitGroundLevel = (bbSelfMin.y < GROUND_LEVEL_Y);

	if ((result && (bbSelfMin.y <= bbOtherMax.y && bbSelfMax.y >= bbOtherMin.y)) || hitGroundLevel) {
		if (this->position.y > bbOtherMax.y) {
			if (!this->isJumping) {
				this->canJump = true;
			}
		}
	}

	return result || hitGroundLevel;
}

