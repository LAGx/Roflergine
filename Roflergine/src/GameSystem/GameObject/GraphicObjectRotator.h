#pragma once
#include "GraphicGameObject.h"

class GraphicObjectRotator : public GraphicGameObject {
public:

	inline static const char* GetClassName() {
		return "graphic_object_rotator";
	}

	// IGameObject (part)
	Error loadFromXml(const tinyxml2::XMLElement*) override;
	void onUpdate(DeltaTimeValue delta) override;

private:
	double speed = 0;
};