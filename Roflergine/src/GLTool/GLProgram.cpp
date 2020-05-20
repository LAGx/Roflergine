#include "GLProgram.h"
#include "GL/glew.h"



Error GLProgram::setupPipeline(const ShaderPipeline& pipeline)
{
	programReady = false;

	if (auto error = pipeline.validate())
		return error;
	
	currentPipeline = pipeline;

	if (auto error = compile())
		return error;

	programReady = true;
	return std::nullopt;
}


void GLProgram::enableThis()
{
	if (programReady)
		glUseProgram(glProgramId);
	else
		disablePrograms();
}

UniformSystem& GLProgram::getUniformSystem()
{
	return uniform;
}


void GLProgram::disablePrograms()
{
	glUseProgram(GL_ZERO);
}

GLProgram::~GLProgram()
{
	if (glProgramId != 0) 
		glDeleteProgram(glProgramId);
}

Error GLProgram::compile()
{
	if (glProgramId != 0) {
		glDeleteProgram(glProgramId);
		glProgramId = 0;
	}

	glProgramId = glCreateProgram();

	for (const auto& shader : currentPipeline.shaderSet) 
		glAttachShader(glProgramId, shader.index);
	
	{ //link
		glLinkProgram(glProgramId);

		GLint linkSuccess;
		glGetProgramiv(glProgramId, GL_LINK_STATUS, &linkSuccess);

		if (!linkSuccess) {
			GLint needSize = 0;
			glGetProgramiv(glProgramId, GL_INFO_LOG_LENGTH, &needSize);
			std::vector<char> log(needSize, 0);

			glGetProgramInfoLog(glProgramId, log.size(), nullptr, log.data());

			return { {"Program link error: " + std::string(log.data()), ErrorCode::Compile} };
		}
	}

	{//validation
		glValidateProgram(glProgramId);

		GLint validateSuccess;
		glGetProgramiv(glProgramId, GL_VALIDATE_STATUS, &validateSuccess);

		if (!validateSuccess) {
			GLint needSize = 0;
			glGetProgramiv(glProgramId, GL_INFO_LOG_LENGTH, &needSize);
			std::vector<char> log(needSize, 0);

			glGetProgramInfoLog(glProgramId, log.size(), nullptr, log.data());

			return { {"Program validate error: " + std::string(log.data()), ErrorCode::Compile} };
		}
	}

	return uniform.setProgramm(glProgramId);
}
