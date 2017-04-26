#include "Character.h"

#include "LightSource.h"

Character::Character()
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->pickingShader = make_unique<Shader>("Resources/Shaders/color_picking.vert", "Resources/Shaders/color_picking.frag");
	this->model = Model("Resources/Models/Cube/cube.dae");
}

Character::~Character()
{
}

void Character::update(float deltaTime)
{
}

void Character::draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources)
{
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

	// send viewer position to the shader:
	glUniform3f(shader->getUniformLocation("viewPos"), camera->position.x, camera->position.y, camera->position.z);

	// apply view and projection matrices:
	glUniformMatrix4fv(shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(*projectionMatrix));

	// draw the loaded model:
	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	this->model.draw(shader.get());
}

void Character::drawPicking(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, GLuint pickingID)
{
	pickingShader->useShader();

	// calculate picking ID of the object:
	GLint r = (pickingID & 0x000000FF) >> 0;
	GLint g = (pickingID & 0x0000FF00) >> 8;
	GLint b = (pickingID & 0x00FF0000) >> 16;
	glUniform4f(pickingShader->getUniformLocation("pickingColor"), r/255.0f, g/255.0f, b/255.0f, 1.0f);

	// send viewer position to the shader:
	glUniform3f(pickingShader->getUniformLocation("viewPos"), camera->position.x, camera->position.y, camera->position.z);

	// apply view and projection matrices:
	glUniformMatrix4fv(pickingShader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(pickingShader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(*projectionMatrix));

	// draw the loaded model:
	glUniformMatrix4fv(pickingShader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	this->model.draw(pickingShader.get());
}