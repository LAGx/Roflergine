#pragma once
#include "../Mesh/Mesh.h"
#include <glm/glm.hpp>
#include <memory>
#include "../GLTool/GLProgram.h"
#include "../Texture/Texture2D.h"

class GraphicObject {
public:

	GraphicObject() = default;

	void setMesh(std::shared_ptr<Mesh>);
	void setTexture(std::shared_ptr<Texture2D>);

	void setPosition(glm::vec3);
	void setScale(glm::vec3);
	//x y z order
	void setRotation(glm::vec3);

	void addPosition(glm::vec3 val);
	void addRotation(glm::vec3 val);
	void addScale(glm::vec3 val);

	void render(GLProgram&);

	void setModelUniform(UniformReference);

private:

	std::shared_ptr<Mesh> mesh = nullptr;
	std::shared_ptr<Texture2D> texture = nullptr;

	glm::vec3 position = glm::vec4(0.0);
	glm::vec3 scale = glm::vec4(1.0);
	glm::vec3 rotation = glm::vec3(0.0);

	UniformReference modelUniform;
};
