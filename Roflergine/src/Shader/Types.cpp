#pragma once
#include "Types.h"
#include <set>
#include <algorithm>

const std::map<std::string, ShaderType> SourceExtentionToShaderTypeMapping = {
	{".frag", ShaderType::Fragment},
	{".vert", ShaderType::Vertex}
};

Error ShaderPipeline::validate() const
{

	std::set<ShaderType> typesSet;

	auto requiredShaders = {
		ShaderType::Vertex,
		ShaderType::Fragment
	};

	//dublication check
	for (const auto& shader : shaderSet) {
		if (typesSet.find(shader.type) != typesSet.end())
			return { {"Shader type dublication in pipeline: `" + std::to_string(static_cast<int>(shader.type)) + "`.", ErrorCode::General} };
		typesSet.insert(shader.type);
	}

	//required shaders check
	for (auto required : requiredShaders) {
		auto found = std::find_if(shaderSet.begin(), shaderSet.end(), [required](const ShaderInfo& info) -> bool {
			return info.type == required;
			});

		if (found == shaderSet.end())
			return { {"Required shader not found: `" + std::to_string(static_cast<int>(required)) + "`.", ErrorCode::General} };
	}

	return std::nullopt;
}
