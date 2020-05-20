#include "DirectionalLightSource.h"
#include "../../../Utils/TimeValue.h"
#include "../../../GLTool/GLProgram.h"
#include <tinyxml2.h>

Error DirectionalLightSource::loadFromXml(const tinyxml2::XMLElement* xml){
	if (auto node = xml->FirstChildElement("Color")) {
		colour.x = node->FloatAttribute("r", colour.x);
		colour.y = node->FloatAttribute("g", colour.y);
		colour.z = node->FloatAttribute("b", colour.z);
	}

	if (auto node = xml->FirstChildElement("Intensity")) {
		intensity = node->FloatAttribute("value", intensity);
	}

	if (auto node = xml->FirstChildElement("Direction")) {
		direction.x = node->FloatAttribute("x", direction.x);
		direction.y = node->FloatAttribute("y", direction.y);
		direction.z = node->FloatAttribute("z", direction.z);
	}

	return std::nullopt;
}

Error DirectionalLightSource::onInit(GLProgram& glProgram){
	Error error;

	error = glProgram.getUniformSystem().registerUniform(DirectionalLightSource::SharedColorUniform);
	if (error)
		return error;

	error = glProgram.getUniformSystem().registerUniform(DirectionalLightSource::SharedIntensUniform);
	if (error)
		return error;

	error = glProgram.getUniformSystem().registerUniform(DirectionalLightSource::SharedDirectionalUniform);
	if (error)
		return error;

	return error;
}

void DirectionalLightSource::render(GLProgram& glProgram){
	glProgram.getUniformSystem().setValue(DirectionalLightSource::SharedColorUniform, colour);
	glProgram.getUniformSystem().setValue(DirectionalLightSource::SharedIntensUniform, intensity);
	glProgram.getUniformSystem().setValue(DirectionalLightSource::SharedDirectionalUniform, direction);
}

void DirectionalLightSource::onUpdate(DeltaTimeValue delta){
}

void DirectionalLightSource::onDestroy(){
}
