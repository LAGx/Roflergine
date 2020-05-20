#pragma once
#include "../Shader/Types.h"
#include "../Utils/Error.h"
#include "../Shader/Uniform/UniformSystem.h"


class GLProgram {
public:

	Error setupPipeline(const ShaderPipeline&);
	
	void enableThis();
	UniformSystem& getUniformSystem();
	
	static void disablePrograms();

	~GLProgram();

private:

	Error compile();

	bool programReady = false;
	ShaderPipeline currentPipeline;
	GLuint glProgramId = 0;
	UniformSystem uniform;
};