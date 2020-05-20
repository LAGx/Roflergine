#include "InertialObject.h"

void BaseInertialObject::setPosition(glm::dvec3 value){
	position = value;
}

void BaseInertialObject::setMass(double kg){
	mass = kg;
}

void BaseInertialObject::setDragForce(double drag){
	dragForce = drag;
}

void BaseInertialObject::setVelocity(glm::dvec3 value){
	velocity = value;
}

void BaseInertialObject::addDImpulse(glm::dvec3 impulse){
	velocity += impulse / mass;
}

glm::dvec3 BaseInertialObject::getPosition() const{
	return position;
}

glm::dvec3 BaseInertialObject::getVelocity() const{
	return velocity;
}

void BaseInertialObject::simulate(DeltaTimeValue delta){
	onPhisicUpdate(delta);
	
	double deltaSeconds = delta.GetSeconds<double>();
	double dragDImpulseLength = dragForce * deltaSeconds;

	if (dragDImpulseLength > 0.0001 && length(velocity) > dragDImpulseLength) {
		glm::dvec3 dragImpulseDirection = -glm::normalize(velocity);
		glm::dvec3 dragDImpulseVector = dragImpulseDirection * dragDImpulseLength;
		velocity += dragDImpulseVector / mass;
	}
	else if (length(velocity) < dragDImpulseLength) {
		velocity = glm::dvec3(0);
	}

	position += velocity * deltaSeconds;
}
