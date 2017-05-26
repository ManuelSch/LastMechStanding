#pragma once

#define _USE_MATH_DEFINES

// C++ libraries:
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <map>

// OpenGL libraries
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// constants:
#define GRAVITY 10.0f
#define GROUND_LEVEL_Y -10.0f

using namespace std;

enum Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
