#include "GraphicObject.h"
#include <glm\ext\matrix_transform.hpp>


void GraphicObject::setMesh(std::shared_ptr<Mesh> ref)
{
	mesh = ref;
}

void GraphicObject::setTexture(std::shared_ptr<Texture2D> ref)
{
	texture = ref;
}

void GraphicObject::setPosition(glm::vec3 val)
{
	position = val;
}

void GraphicObject::addPosition(glm::vec3 val)
{
	position += val;
}


void GraphicObject::setScale(glm::vec3 val)
{
	scale = val;
}

void GraphicObject::addRotation(glm::vec3 val)
{
	rotation += val;
}

void GraphicObject::addScale(glm::vec3 val)
{
	scale += val;
}

void GraphicObject::setRotation(glm::vec3 val)
{
	rotation = val;
}


void GraphicObject::render(GLProgram& program)
{
	if (!mesh)
		return;

	auto translationMatrix = glm::translate(glm::mat4(1.0f), position);
	auto scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 rotateMatrix(1.0);
	rotateMatrix = glm::rotate(rotateMatrix, rotation.x, glm::vec3(1.0f, 0, 0));
	rotateMatrix = glm::rotate(rotateMatrix, rotation.y, glm::vec3(0, 1.0f, 0));
	rotateMatrix = glm::rotate(rotateMatrix, rotation.z, glm::vec3(0, 0, 1.0f));

	auto model = translationMatrix * rotateMatrix * scaleMatrix;

	program.getUniformSystem().setValue(modelUniform, model);

	if(texture)
		texture->use();
	mesh->render();
}

void GraphicObject::setModelUniform(UniformReference val)
{
	modelUniform = val;
}

