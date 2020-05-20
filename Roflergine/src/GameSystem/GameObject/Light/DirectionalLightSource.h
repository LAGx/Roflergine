#pragma once
#include "../../IGameObject.h"
#include "../../../GLTool/GLProgram.h"
#include <glm/glm.hpp>


class DirectionalLightSource : public IGameObject {
public:

	inline static const char* GetClassName() {
		return "light_directional";
	}

	// IGameObject
	Error loadFromXml(const tinyxml2::XMLElement*) override;
	Error onInit(GLProgram& glProgram) override;
	void render(GLProgram& glProgram) override;
	void onUpdate(DeltaTimeValue delta) override;
	void onDestroy() override;

private:
	inline static UniformReference SharedColorUniform = UniformReference("directionalLightParam.colour");
	inline static UniformReference SharedIntensUniform = UniformReference("directionalLightParam.intensity");
	inline static UniformReference SharedDirectionalUniform = UniformReference("directionalLightParam.direction");

	glm::vec3 colour = { 1.0f, 1.0f, 1.0f };
	float intensity = 1.0f;
	glm::vec3 direction = { 1.0f, 0.0f, 0.0f };
};