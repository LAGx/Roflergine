#pragma once
#include <GL/glew.h>
#include <map>
#include <string>
#include "../Utils/Error.h"


enum class ShaderType: GLenum {
	Undefined = 0,
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER
};


struct ShaderInfo {
	GLuint index = 0;
	ShaderType type = ShaderType::Undefined;
};


struct ShaderPipeline {
	std::vector<ShaderInfo> shaderSet;

	//check for all needed shader exist
	//and no dublication
	Error validate() const;
};


extern const std::map<std::string, ShaderType> SourceExtentionToShaderTypeMapping;


