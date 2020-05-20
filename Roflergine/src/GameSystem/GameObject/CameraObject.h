#pragma once
#include "../IGameObject.h"
#include "../../Phisic/InertialObject.h"
#include "../../Window/IControlHandler.h"
#include "../SystemManager/SystemManager.h"

class CameraObject: public IGameObject, public BaseInertialObject, public IControlHandler {
public:

	inline static const char* GetClassName() {
		return "camera";
	}

	// IGameObject
	Error loadFromXml(const tinyxml2::XMLElement*) override;
	Error onInit(GLProgram& glProgram) override;
	void render(GLProgram& glProgram) override;
	void onUpdate(DeltaTimeValue delta) override;
	void onDestroy() override;

	// IControlHandler
	void OnKeyButtonPressing(int key) override;
	void OnMouseMovement(double x, double y) override;

private:
	inline static UniformReference ViewlUniform = UniformReference("view");
	inline static UniformReference ProjectionUniform = UniformReference("projection");

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

	glm::dvec3 rotation = glm::vec3(0);
	glm::dvec2 lastMousePosition = glm::vec2(0);
	float fov = 45.0;

	glm::dvec3 resetPosition = glm::vec3(0);
	glm::dvec3 resetRotation = glm::vec3(0);
	bool firstMouseEvent = true;
};
