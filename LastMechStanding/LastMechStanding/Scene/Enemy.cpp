#include "Enemy.h"

#include "LightSource.h"


Enemy::Enemy()
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->model = Model("Resources/Models/Enemy/enemy.dae");
	
	this->health = 500;
	this->movedirection = glm::vec3(0, 0, 0);
	this->moveSpeed = 3;
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
	//auto lastMoveDirection = movedirection;
	glm::vec4 enemyPosition = this->modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 destination = glm::vec3(1.0f, 1.0f, 0.0f);

	movedirection = destination - glm::vec3(enemyPosition.x, enemyPosition.y, enemyPosition.z);

	movedirection = glm::normalize(movedirection);

	//tried to rotate object to direction but didn't work
	//auto dot = glm::dot(movedirection, lastMoveDirection);
	//auto angle = glm::acos(dot);
	//glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
	

	glm::vec3 movement = glm::vec3(movedirection.x * moveSpeed * deltaTime,
		movedirection.y * moveSpeed * deltaTime,
		movedirection.z * moveSpeed * deltaTime);


	//cube is moving, but spawns in wrong destination
	//modelMatrix = glm::translate(glm::mat4(1.0), movement) * modelMatrix;

	//cube is orbiting and moving to direction, also from false spawn point
	//this->translate(movement);

}

void Enemy::move() {
	
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
