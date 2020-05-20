#pragma once
#include "../IGameObject.h"
#include "../../Object/GraphicObject.h"

class GraphicGameObject : public IGameObject {
public:

	inline static const char* GetClassName() { 
		return "graphic_object"; 
	}

	// IGameObject
	Error loadFromXml(const tinyxml2::XMLElement*) override;
	Error onInit(GLProgram& glProgram) override;
	void render(GLProgram& glProgram) override;
	void onUpdate(DeltaTimeValue delta) override;
	void onDestroy() override;

protected:
	inline static UniformReference SharedModelUniform = UniformReference("model");
	GraphicObject graphic;
};