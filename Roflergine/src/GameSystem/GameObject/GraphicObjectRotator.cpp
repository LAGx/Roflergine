#include "GraphicObjectRotator.h"
#include "tinyxml2.h"
#include "../../Utils/TimeValue.h"

Error GraphicObjectRotator::loadFromXml(const tinyxml2::XMLElement* xml){
	auto error = GraphicGameObject::loadFromXml(xml);

	if (const auto node = xml->FirstChildElement("RotationSpeed")) {
		speed = node->FloatAttribute("value");
	}
	else {
		return { {"GraphicObjectRotator can`t find RotationSpeed tag.", ErrorCode::FileParse} };
	}

	return error;
}

void GraphicObjectRotator::onUpdate(DeltaTimeValue delta){
	GraphicGameObject::onUpdate(delta);
	graphic.addRotation({0, speed, 0});
}
