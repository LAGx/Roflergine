#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class BaseLightSource {
public:
	glm::vec3 baseColor = { 1.0, 1.0, 1.0 };
	GLfloat intence = 1.0;
};