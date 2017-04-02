#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

// OpenGL Libraries:
#include <glm/glm.hpp>
#include <glew.h>
#include <glm\gtc\matrix_transform.hpp>

// game specific includes:
#include "..\Util\Shader.h"
#include "..\Scene\SceneObject.h"
#include "..\objloader\objloader.hpp"


#ifdef SCENE_OBJECT

namespace scene {
	class Cube : public SceneObject
	{
	public:
		Cube();
		Cube(glm::mat4& matrix, util::Shader* shader);
		virtual ~Cube();

		virtual void update(float time_delta);
		virtual void draw();

	private:
		GLuint vao;
		GLuint positionBuffer, normalsBuffer, indexBuffer;
		util::Shader* shader;

		static const float positions[24 * 3];
		static const unsigned int indices[36];
		static const float normals[24 * 3];

		std::vector< glm::vec3 > _vertices;
		std::vector< glm::vec2 > _uvs;
		std::vector< glm::vec3 > _normals;

		//void InitMesh(const IndexedModel& model);
	};
}

#endif
