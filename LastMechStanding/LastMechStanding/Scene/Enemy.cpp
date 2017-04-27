#include "Enemy.h"

Enemy::Enemy()
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->model = Model("Resources/Models/Cube/cube.dae");
	this->health = 500;
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
}

void Enemy::draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix, Camera* camera, vector<shared_ptr<LightSource>>* lightSources)
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

void Enemy::hitEnemy(int damage) {
	int newhealth = this->health - damage;

	if (newhealth <= 0) {
		//enemy dead
	}
	else {
		this->health = newhealth;
	}
}
