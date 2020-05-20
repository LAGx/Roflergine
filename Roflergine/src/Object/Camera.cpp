#include "Camera.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm\ext\matrix_transform.hpp>
#include "../Math/VectorMath.h"

using namespace std;

/*
Camera::Camera(){
	setDragForce(10);
}

glm::mat4 Camera::getView() const{
	glm::dmat4 result = vectorToRotationMatrix(rotation);
	result = glm::translate(result, this->getPosition());
	return result;
}

void Camera::OnKeyButtonPressing(int key){
	double speed = 0.5;
	glm::dvec4 direction(0);

	if (key == GLFW_KEY_W){
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
	else if (key == GLFW_KEY_F) {
		setPosition({ 0,0,0 });
		rotation  = { 0,0,0 };
	}

	if (glm::length(direction) != 0) {
		auto cameraRotate = vectorToRotationMatrix(rotation);
		auto impulse = glm::normalize(direction) * speed;
		auto impulceInCameraSpace = glm::inverse(cameraRotate) * impulse;
		this->addDImpulse(impulceInCameraSpace);
	}
}

void Camera::OnMouseMovement(double x, double y){
	float sensivity = 0.001;
	
	glm::dvec2 currentMouse(x, y);

	auto deltaMouse = currentMouse - lastMousePosition;

	lastMousePosition = currentMouse;

	rotation.y += deltaMouse.x * sensivity;
	rotation.x += deltaMouse.y * sensivity;     
}

void Camera::onUpdate(DeltaTimeValue){
	//todo camera movement
}
*/