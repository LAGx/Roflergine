#include "CameraObject.h"
#include "../SceneParserUtils/TagTransformParser.h"
#include <glm\ext\matrix_transform.hpp>
#include "../../Math/VectorMath.h"
#include <glm\ext\matrix_clip_space.hpp>
#include <iostream>
#include "../../GLTool/GLProgram.h"

Error CameraObject::loadFromXml(const tinyxml2::XMLElement* xml){
	TagTransformParser transform;
	Error error;

	error = transform.load(xml->FirstChildElement(TagTransformParser::Name));
	if (error)
		return error;

	this->setPosition(transform.position);
	rotation = transform.rotation;

	resetRotation = transform.rotation;
	resetPosition = transform.position;

	if (auto FovXML = xml->FirstChildElement("Fov")) {
		fov = FovXML->FloatAttribute("value", fov);
	}

	this->setDragForce(20);
	return std::nullopt;
}

Error CameraObject::onInit(GLProgram& glProgram){
	Error error;
	
	error = glProgram.getUniformSystem().registerUniform(CameraObject::ProjectionUniform);
	if (error)
		return error;

	error = glProgram.getUniformSystem().registerUniform(CameraObject::ViewlUniform);
	if (error)
		return error;

	g_manager.GetWindow().registerListener(dynamic_cast<IControlHandler*>(this));
	
	return std::nullopt;
}

void CameraObject::render(GLProgram& glProgram){
	glProgram.getUniformSystem().setValue(CameraObject::ViewlUniform, getView());
	glProgram.getUniformSystem().setValue(CameraObject::ProjectionUniform, getProjection());
}

void CameraObject::onUpdate(DeltaTimeValue delta){
}

void CameraObject::onDestroy(){
	g_manager.GetWindow().unregisterListener(dynamic_cast<IControlHandler*>(this));
}

void CameraObject::OnKeyButtonPressing(int key){
	double speed = 1.0;
	glm::dvec4 direction(0);

	if (key == GLFW_KEY_W) {
		direction.z = 1;
	}
	else if (key == GLFW_KEY_S) {
		direction.z = -1;
	}
	else if (key == GLFW_KEY_D) {
		direction.x = -1;
	}
	else if (key == GLFW_KEY_A) {
		direction.x = 1;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT) {
		direction.y = -1;
	}
	else if (key == GLFW_KEY_LEFT_CONTROL) {
		direction.y = 1;
	}
	else if (key == GLFW_KEY_F) {
		setPosition(resetPosition);
		rotation = resetRotation;
		setVelocity({0,0,0});
	}
	
	if (glm::length(direction) != 0) {
		//auto cameraRotate = vectorToRotationMatrix(rotation);
		//auto impulse = glm::normalize(direction) * speed;
		//auto impulceInCameraSpace = glm::inverse(cameraRotate) * impulse;
		//this->addDImpulse(impulceInCameraSpace);

		auto cameraRotate = vectorToRotationMatrix(glm::vec3(0, rotation.y, 0));
		auto impulse = glm::normalize(direction) * speed;
		auto impulceInCameraSpace = glm::inverse(cameraRotate) * impulse;
		this->addDImpulse(impulceInCameraSpace);
	}
}

void CameraObject::OnMouseMovement(double x, double y) {
	float sensivity = 0.001;

	glm::dvec2 currentMouse(x, y);

	auto deltaMouse = currentMouse - lastMousePosition;


	lastMousePosition = currentMouse;

	if (firstMouseEvent) {
		firstMouseEvent = false;
	}
	else {

		rotation.y += deltaMouse.x * sensivity;
		rotation.x += deltaMouse.y * sensivity;
	}
}

glm::mat4 CameraObject::getView() const{
	glm::dmat4 result = vectorToRotationMatrix(rotation);
	result = glm::translate(result, this->getPosition());
	return result;
}

glm::mat4 CameraObject::getProjection() const{
	return glm::perspective(-fov, (float)g_manager.GetWindow().getAspectRatio(), 0.1f, 1000.0f);
}
