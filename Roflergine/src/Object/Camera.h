//#include <glm/glm.hpp>
//#include "../Window/IControlHandler.h"
//#include "../Phisic/InertialObject.h"
//
/*
[DEPRACATED]
class Camera: public IControlHandler, public BaseInertialObject {
public:
	Camera();
	glm::mat4 getView() const;

private:
	void OnKeyButtonPressing(int key) override;
	void OnMouseMovement(double x, double y) override;

	void onUpdate(DeltaTimeValue) override;
private:
	glm::dvec3 rotation = glm::vec3(0);
	glm::dvec2 lastMousePosition = glm::vec2(0);
};
*/