#include "UniformSystem.h"
#include <glm/gtc/type_ptr.hpp>

Error UniformSystem::setProgramm(GLuint id){
	if (programid == id)
		return std::nullopt;

	programid = id;

	//registeredUniform changes in registerUniform
	auto registeredUniformCopy = registeredUniform;
	registeredUniform.clear();

	for (auto& uniform : registeredUniformCopy)
	{
		auto error = registerUniform(uniform.second, true);

		if (error)
			return error;
	}

	return std::nullopt;
}


Error UniformSystem::registerUniform(UniformReference& uniform, bool force_register){
	if (!force_register) {
		auto found = registeredUniform.find(uniform.name);

		if (found != registeredUniform.end()) {
			if (found->second.isValid()) {
				uniform = found->second;
				return std::nullopt;
			}
		}
	}

	if (programid != 0){
		auto id = glGetUniformLocation(programid, uniform.name.c_str());
		
		if (id == -1)
			return { {"Can`t register uniform: " + uniform.name, ErrorCode::Init} };
		
		uniform.glId = id;
	}

	registeredUniform[uniform.name] = uniform;

	return std::nullopt;
}


void UniformSystem::setValue(const UniformReference& ref, const glm::mat4& data){
	if (ref.isValid() && programid != 0) 
		glUniformMatrix4fv(ref.glId, 1, GL_FALSE, glm::value_ptr(data));
}

void UniformSystem::setValue(const UniformReference& ref, glm::vec3 data){
	if (ref.isValid() && programid != 0)
		glUniform3f(ref.glId, data.x, data.y, data.z);
}

void UniformSystem::setValue(const UniformReference& ref, float data){
	if (ref.isValid() && programid != 0)
		glUniform1f(ref.glId, data);
}

void UniformSystem::setValue(const UniformReference& ref, int data){
	if (ref.isValid() && programid != 0)
		glUniform1i(ref.glId, data);
}

void UniformSystem::unregisterAll(){
	registeredUniform.clear();
}


UniformSystem::~UniformSystem(){
	unregisterAll();
}
