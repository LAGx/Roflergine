#pragma once
#include <filesystem>
#include "../Utils/Error.h"
#include "../Utils/System.h"
#include "Types.h"



class ShaderManager {
public:

	static Error compileShader(std::filesystem::path, _out_ ShaderInfo&);

private:

	//input filename.extention / extention / full path.extention
	static Error extentionToType(std::filesystem::path, _out_ ShaderType&);

};