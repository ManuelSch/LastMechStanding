#pragma once

// OpenGL Libraries:
#include <glm/glm.hpp>
#include <glew.h>
#include <glm\gtc\matrix_transform.hpp>

// game specific includes:
#include "..\Resources\Shader.h"
#include "..\Scene\SceneObject.h"
#ifdef SCENE_OBJECT

namespace scene {
	class Cube : public SceneObject
	{
	public:
		Cube();
		Cube(glm::mat4& matrix, resources::Shader* shader);
		virtual ~Cube();

		virtual void update(float time_delta);
		virtual void draw();

	private:
		GLuint vao;
		GLuint positionBuffer, normalsBuffer, indexBuffer;
		resources::Shader* shader;

		static const float positions[24 * 3];
		static const unsigned int indices[36];
		static const float normals[24 * 3];
	};
}

#endif
