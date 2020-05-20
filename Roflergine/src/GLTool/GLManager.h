#pragma once
#include <GL\glew.h>
#include "../Utils/Error.h"


class GLManager {
public:
	Error init();
	void clearFrame();
	void flush();
	void setViewportSize(GLsizei x, GLsizei y);
};