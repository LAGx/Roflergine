#pragma once
#include "../Utils/Error.h"

class GLProgram;
class DeltaTimeValue;

namespace tinyxml2 {
	class XMLElement;
}

class IGameObject {
public:
	virtual ~IGameObject() = default;

	virtual Error loadFromXml(const tinyxml2::XMLElement*) = 0;
	virtual Error onInit(GLProgram& glProgram) = 0;
	virtual void render(GLProgram& glProgram) = 0;
	virtual void onUpdate(DeltaTimeValue delta) = 0;
	virtual void onDestroy() = 0;
};