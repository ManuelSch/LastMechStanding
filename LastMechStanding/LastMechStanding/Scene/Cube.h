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
#include "..\External\classes\objloader\objloader.hpp"

// game specific includes:
#include "..\Util\Shader.h"
#include "..\Scene\SceneObject.h"


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
		GLuint positionBuffer, normalsBuffer, uvBuffer, indexBuffer;
		util::Shader* shader;

		//static const float POSITIONS[24 * 3];
		//static const unsigned int INDICES[36];
		//static const float NORMALS[24 * 3];
		//static const float UVS[24 * 2];

		std::vector< glm::vec3 > positions;
		std::vector< glm::vec2 > indices;
		std::vector< glm::vec2 > uvs;
		std::vector< glm::vec3 > normals;
	};
}

#endif
