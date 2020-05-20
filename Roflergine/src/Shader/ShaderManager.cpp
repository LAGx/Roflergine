#include "ShaderManager.h"
#include "regex"
#include <fstream>
#include "../Settings.h"
#include "../Utils/System.h"


using namespace std;

Error ShaderManager::compileShader(std::filesystem::path sourcePath, _out_ ShaderInfo& shader){

	auto extentionConvertError = extentionToType(sourcePath, shader.type);

	if (extentionConvertError)
		return extentionConvertError;

	shader.index = glCreateShader((GLenum)shader.type);

	ifstream fstream(sourcePath);

	if (!fstream.is_open())
		return { {"Can`t open file.", ErrorCode::FileOpen} };

	string sourceCode((istreambuf_iterator<char>(fstream)), (istreambuf_iterator<char>()));

	const GLchar* sourcesArray[1];
	sourcesArray[0] = sourceCode.data();

	GLint sourcesLength[1];
	sourcesLength[0] = VECTOR_SIZE_IN_BYTES(sourceCode);

	glShaderSource(shader.index, 1, sourcesArray, sourcesLength);
	glCompileShader(shader.index);


	GLint success = 0;

	glGetShaderiv(shader.index, GL_COMPILE_STATUS, &success);

	if (!success) {

		GLint needSize = 0;
		glGetShaderiv(shader.index, GL_INFO_LOG_LENGTH, &needSize);
		vector<char> log(needSize, 0); 

		glGetShaderInfoLog(shader.index, log.size(), nullptr, log.data());

		return { {"Shader compile error: " + string(log.data()), ErrorCode::Compile} };
	}

	return nullopt;
}


Error ShaderManager::extentionToType(std::filesystem::path filepath, _out_ ShaderType& type){

	string extention = filepath.extension().u8string();

	auto foundType = SourceExtentionToShaderTypeMapping.find(extention);

	if (foundType == SourceExtentionToShaderTypeMapping.end())
		return { {string() + "Can`t recognize extention as shader source.\nfile path: " + filepath.u8string() + "\nparsed extention: " + extention, ErrorCode::FileName} };

	type = foundType->second;

	return nullopt;
}