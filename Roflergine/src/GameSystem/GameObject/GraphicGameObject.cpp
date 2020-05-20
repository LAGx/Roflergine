#include "GraphicGameObject.h"
#include "../SceneParserUtils/TagTransformParser.h"
#include "../../Utils/TimeValue.h"
#include <memory>

Error GraphicGameObject::loadFromXml(const tinyxml2::XMLElement* xml){
	TagTransformParser transform(xml->FirstChildElement(TagTransformParser::Name));
	std::shared_ptr<Mesh> mesh(new Mesh());
	std::shared_ptr<Texture2D> texture(new Texture2D());

	if (const auto xmesh = xml->FirstChildElement("Mesh")) {
		if (const auto path = xmesh->Attribute("path")) {
			auto error = mesh->loadFromFile(path);
			if (error)
				return error;
		}
		else {
			return { {"In Mash tag not exist `path` attribue.", ErrorCode::FileParse} };
		}
	}
	else {
		return { {"GraphicGameObject can`t find Mesh tag.", ErrorCode::FileParse} };
	}

	if (const auto xmesh = xml->FirstChildElement("Texture2D")) {
		if (const auto path = xmesh->Attribute("path")) {
			auto error = texture->loadFromFile(path);
			if (error)
				return error;
		}
		else {
			return { {"In Texture2D tag not exist `path` attribue.", ErrorCode::FileParse} };
		}
	}
	else {
		return { {"GraphicGameObject can`t find Texture2D tag.", ErrorCode::FileParse} };
	}

	graphic.setMesh(mesh);
	graphic.setTexture(texture);
	graphic.setPosition(transform.position);
	graphic.setRotation(transform.rotation);
	graphic.setScale(transform.scale);

	return std::nullopt;
}

Error GraphicGameObject::onInit(GLProgram& program){
	auto error = program.getUniformSystem().registerUniform(GraphicGameObject::SharedModelUniform);
	graphic.setModelUniform(SharedModelUniform);
	return error;
}

void GraphicGameObject::render(GLProgram& glProgram){
	graphic.render(glProgram);
}

void GraphicGameObject::onUpdate(DeltaTimeValue delta){
}

void GraphicGameObject::onDestroy(){
}
