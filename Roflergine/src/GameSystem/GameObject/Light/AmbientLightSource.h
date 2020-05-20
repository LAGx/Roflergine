#pragma once
#include "../../IGameObject.h"
#include "../../../GLTool/GLProgram.h"
#include <glm/glm.hpp>


class AmbientLightSource : public IGameObject {
public:

	inline static const char* GetClassName() {
		return "light_ambient";
	}

	// IGameObject
	Error loadFromXml(const tinyxml2::XMLElement*) override;
	Error onInit(GLProgram& glProgram) override;
	void render(GLProgram& glProgram) override;
	void onUpdate(DeltaTimeValue delta) override;
	void onDestroy() override;

private:
	inline static UniformReference SharedColorUniform = UniformReference("ambientLightParam.colour");
	inline static UniformReference SharedIntensUniform = UniformReference("ambientLightParam.intensity");

	glm::vec3 colour = {1.0f, 1.0f, 1.0f};
	float intensity = 1.0f;
};