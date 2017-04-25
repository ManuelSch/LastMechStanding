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

void Character::draw(Camera* camera, Display* display)
{
	shader->useShader();

	// transformation matrices:
	glm::mat4 projection = glm::perspective(camera->zoom, (float)display->width / (float)display->height, 0.1f, 100.0f);
	glm::mat4 view = camera->getViewMatrix();
	glUniformMatrix4fv(shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));

	// draw the loaded model:
	glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	this->model.draw(shader.get());
}
