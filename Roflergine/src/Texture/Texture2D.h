#pragma once
#include "GL/glew.h"
#include "SOIL.h"
#include "../Utils/System.h"
#include "../Utils/Error.h"
#include <string>
#include <filesystem>
#include <optional>


class Texture2D {
public:
	~Texture2D();

	Error loadFromFile(const std::filesystem::path&);
	void use();
	void reset();

private:
	
	bool texture_ready = false;
	GLuint glId;
	struct {
		i32 x = 0;
		i32 y = 0;
		i32 depth = 0;
	}size;
};