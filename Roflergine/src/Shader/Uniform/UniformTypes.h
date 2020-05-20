#pragma once
#include <string>
#include "GL/glew.h"



struct UniformReference {

	UniformReference() = default;

	UniformReference(std::string _name)
		:name(std::move(_name))
	{}

	bool isValid() const {
		return glId != -1;
	}

	std::string name = "default";
	GLint glId = -1;
};


