#pragma once

#include "..\commonHeader.h"

class LightSource
{
public:
	enum Type {
		DIRECTIONAL,
		POINT
	};

	LightSource(Type type);
	~LightSource();

	Type type;

	// general light parameters:
	glm::vec3 direction;
	glm::vec3 ambient, diffuse, specular;

	// for point lights only:
	glm::vec3 position;
};
