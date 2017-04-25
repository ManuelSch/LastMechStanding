#include "Character.h"


Character::Character()
{
	this->shader = make_unique<Shader>("Resources/Shaders/model_loading.vert", "Resources/Shaders/model_loading.frag");
	this->model = Model("Resources/Models/Cube/cube.obj");
}

Character::~Character()
{
}

void Character::update(float deltaTime)
{
}

void Character::draw(glm::mat4* viewMatrix, glm::mat4* projectionMatrix)
{
	shader->useShader();

	// apply view and projection matrices:
	glUniformMatrix4fv(shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(*projectionMatrix));

	// draw the loaded model:
	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	this->model.draw(shader.get());
}
