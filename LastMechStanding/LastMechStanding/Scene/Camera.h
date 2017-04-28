#pragma once

#include "..\commonHeader.h"


// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

	// camera Attributes:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// eular angles:
	GLfloat yaw, pitch;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	glm::mat4 getViewMatrix();
	~Camera();
	void updateCameraVectors(glm::vec3 position, glm::vec3 angle);
private:
};