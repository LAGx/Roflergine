#pragma once
#include "Texture2D.h"

Texture2D::~Texture2D() {
	reset();
}

Error Texture2D::loadFromFile(const std::filesystem::path& filepath){
	
	reset();

	auto data = SOIL_load_image(filepath.string().c_str(), &size.x, &size.y, &size.depth, SOIL_LOAD_RGBA);

	if (!data) {
		return { {std::string() + "Falied to load file `" + filepath.string() + "`: " + SOIL_last_result(), ErrorCode::FileOpen} };
	}

	glGenTextures(1, &glId);
	glBindTexture(GL_TEXTURE_2D, glId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(data);
	texture_ready = true;

	return std::nullopt;
}

void Texture2D::use(){
	if (texture_ready) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, glId);
	}
}

void Texture2D::reset(){
	if (texture_ready){
		texture_ready = false;
		glDeleteTextures(1, &glId);
		size = { 0, 0, 0 };
	}
}
