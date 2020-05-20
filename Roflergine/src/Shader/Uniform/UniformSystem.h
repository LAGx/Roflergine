#pragma once
#include <GL\glew.h>
#include "UniformTypes.h"
#include <glm/glm.hpp>
#include <string>
#include <map>
#include "../../Utils/Error.h"


class UniformSystem {
public:
	Error setProgramm(GLuint id);

	Error registerUniform(UniformReference& ref, bool forceRegister = false);

	void setValue(const UniformReference& ref, const glm::mat4& data);
	void setValue(const UniformReference& ref, glm::vec3 data);
	void setValue(const UniformReference& ref, float data);
	void setValue(const UniformReference& ref, int data);

	void unregisterAll();

	~UniformSystem();

private:
	GLuint programid = 0;
	std::map<std::string, UniformReference> registeredUniform;
};