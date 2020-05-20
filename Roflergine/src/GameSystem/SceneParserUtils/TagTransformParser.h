#pragma once
#include <tinyxml2.h>
#include <glm/glm.hpp>
#include "../../Utils/Error.h"

class TagTransformParser {
public:

	TagTransformParser() {}

	TagTransformParser(const tinyxml2::XMLElement* xml) {
		load(xml);
	}

	Error load(const tinyxml2::XMLElement* xml) {

		if (xml == nullptr)
			return { {"Xml element is nullptr.", ErrorCode::Nullptr} };

		if (const auto* tag = xml->FirstChildElement("Position")) {
			position = tagToVec(tag);
		}

		if (const auto* tag = xml->FirstChildElement("Rotation")) {
			rotation = tagToVec(tag);
		}

		if (const auto* tag = xml->FirstChildElement("Scale")) {
			scale = tagToVec(tag);
		}
		
		return std::nullopt;
	}

	inline static const char* Name = "Transform";
	glm::dvec3 position = {0,0,0};
	glm::dvec3 rotation = {0,0,0};
	glm::dvec3 scale = {0,0,0};

private:

	glm::vec3 tagToVec(const tinyxml2::XMLElement* xml) {
		return { xml->DoubleAttribute("x"), xml->DoubleAttribute("y"), xml->DoubleAttribute("z") };
	}
};