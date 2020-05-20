#include "AmbientLightSource.h"
#include "../../../Utils/TimeValue.h"
#include "../../../GLTool/GLProgram.h"
#include <tinyxml2.h>


Error AmbientLightSource::loadFromXml(const tinyxml2::XMLElement* xml){

	if (auto node = xml->FirstChildElement("Color")) {
		colour.x = node->FloatAttribute("r", colour.x);
		colour.y = node->FloatAttribute("g", colour.y);
		colour.z = node->FloatAttribute("b", colour.z);
	}

	if (auto node = xml->FirstChildElement("Intensity")) {
		intensity = node->FloatAttribute("value", intensity);
	}

	return std::nullopt;
}

Error AmbientLightSource::onInit(GLProgram& glProgram){
	
	Error error;

	error = glProgram.getUniformSystem().registerUniform(AmbientLightSource::SharedColorUniform);
	if (error)
		return error;

	error = glProgram.getUniformSystem().registerUniform(AmbientLightSource::SharedIntensUniform);
	if (error)
		return error;

	return error;
}

void AmbientLightSource::render(GLProgram& glProgram){
	glProgram.getUniformSystem().setValue(AmbientLightSource::SharedColorUniform, colour);
	glProgram.getUniformSystem().setValue(AmbientLightSource::SharedIntensUniform, intensity);
}

void AmbientLightSource::onUpdate(DeltaTimeValue delta){
}

void AmbientLightSource::onDestroy(){
}
