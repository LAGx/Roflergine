#include "GLManager.h"
#include <string>

using namespace std;


Error GLManager::init() {
	glewExperimental = GL_TRUE;

	auto initCode = glewInit();

	if (initCode != GLEW_OK) 
		return { { "GLEW init falied with code: " + to_string(initCode), ErrorCode::Init} };
	
	glEnable(GL_DEPTH_TEST);

	return nullopt;
}

void GLManager::clearFrame(){
	glClearColor(0.1, 0.1, 0.15, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLManager::flush(){
	glFlush();
}

void GLManager::setViewportSize(GLsizei x, GLsizei y) {
	glViewport(0, 0, x, y);
}