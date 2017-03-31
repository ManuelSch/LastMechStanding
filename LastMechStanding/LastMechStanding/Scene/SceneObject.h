#pragma once

// OpenGL Libraries:
#include <glm/glm.hpp>

namespace scene {
	class SceneObject
	{
	public:
		SceneObject() : modelMatrix(glm::mat4(1.0f)) {}
		SceneObject(glm::mat4& modelMatrix);
		virtual ~SceneObject();

		virtual void draw() = 0;
		virtual void update(float time_delta) = 0;
		glm::mat4 modelMatrix;
	};
}

#define SCENE_OBJECT