#pragma once 
#include "IPhisicSimutatable.h"
#include <glm\glm.hpp>


class BaseInertialObject: public IPhisicSimulatable {
public:
	BaseInertialObject() = default;
	virtual ~BaseInertialObject() = default;

	void setPosition(glm::dvec3);
	void setMass(double kg);
	void setDragForce(double);
	void setVelocity(glm::dvec3);
	void addDImpulse(glm::dvec3);

	glm::dvec3 getPosition() const;
	glm::dvec3 getVelocity() const;

protected:
	virtual void onPhisicUpdate(DeltaTimeValue) {}

private:
	void simulate(DeltaTimeValue) override;

	double mass = 1.0;
	double dragForce = 0.0;
	glm::dvec3 velocity = glm::dvec3(0);
	glm::dvec3 position = glm::dvec3(0);
};