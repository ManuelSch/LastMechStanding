#pragma once

// OpenGL Libraries:
#include <glm/glm.hpp>
#include <glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include "obj_loader\obj_loader.h"

// game specific includes:
#include "..\Util\Shader.h"
#include "..\Scene\SceneObject.h"
#ifdef SCENE_OBJECT

namespace scene {
	class Cube : public SceneObject
	{
	public:
		Cube();
		Cube(std::string& fileName);
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

		//void InitMesh(const IndexedModel& model);
	};
}

#endif
