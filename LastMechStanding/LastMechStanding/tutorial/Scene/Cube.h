#pragma once

#include <glew.h>
#include "..\Resources\Shader.h"
#include "..\Scene\SceneObject.h"
#ifdef SCENE_OBJECT


#define CUBE_VERTEX_COUNT 8
#define CUBE_INDEX_COUNT 36

namespace cgue {
	namespace scene {
		class Cube : public SceneObject
		{
		public:
			Cube();
			Cube(glm::mat4& matrix, Shader* shader);
			virtual ~Cube();

			virtual void update();
			virtual void draw();

		private:
			GLuint vao;
			GLuint positionBuffer, indexBuffer;
			Shader* shader;

			static const float positions[CUBE_VERTEX_COUNT * 3];
			static const unsigned int indices[CUBE_INDEX_COUNT];

		};
	}
}

#endif
