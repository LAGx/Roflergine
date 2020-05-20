#include "GameScene.h"
#include <fstream>
#include <vector>
#include <tinyxml2.h>

using namespace tinyxml2;

GameScene::GameScene()
{
}

GameScene::~GameScene(){
	reset();
}

ErrorList GameScene::loadScene(const std::filesystem::path& filepath){
	reset();

	ErrorList errors;
	XMLDocument xml;
	auto error = xml.LoadFile(filepath.string().c_str());

	if (error)
		return { { {std::string() + "Error on loading scene file: " + filepath.string() + ".Parser error code: " + std::to_string(error), ErrorCode::FileOpen} } };

	if (const auto* root = xml.FirstChildElement("Scene")) {

		const auto* child = root->FirstChildElement("GameObject");

		while (child) {

			if (child->BoolAttribute("enabled", true)) {

				if (const auto className = child->Attribute("class")) {
					auto obj = GameObjectRegister::Generate(className);

					if (!obj.as_game_object) {
						errors += { {std::string() + "Game object class with name `" + className + "` does nor exist", ErrorCode::FileParse}};
					}
					else {

						objects_usage.push_back(obj);
						objects.push_back(obj.as_game_object);
						errors += objects.back()->loadFromXml(child);

						if (obj.as_phisic_object)
							phisicWorld.registerObject(obj.as_phisic_object);
					}
				}
			}

			child = child->NextSiblingElement("GameObject");
		}
	}

	return errors;
}

ErrorList GameScene::init(){
	ErrorList errors;

	errors += setupGLProgram();

	for (auto& obj : objects) {
		errors += obj->onInit(glProgram);
	}

	return errors;
}

void GameScene::update(DeltaTimeValue delta){
	
	phisicWorld.simulate(delta);

	glProgram.enableThis();

	for (auto& obj : objects) {
		obj->onUpdate(delta);
		obj->render(glProgram);
	}

	glProgram.disablePrograms();
}

void GameScene::reset(){
	for (auto& obj : objects_usage) {
		if(obj.as_game_object)
			obj.as_game_object->onDestroy();
		if (obj.as_phisic_object)
			phisicWorld.unregisterObject(obj.as_phisic_object);
		delete obj.core;
	}
	objects_usage.clear();
	objects.clear();
}

Error GameScene::setupGLProgram(){
	ShaderInfo buffShader;
	ShaderPipeline pipeline;
	Error error;

	error = ShaderManager::compileShader("resources/shaders/default.frag", buffShader);
	if (error)
		return error;
	
	pipeline.shaderSet.push_back(buffShader);

	error = ShaderManager::compileShader("resources/shaders/default.vert", buffShader);
	if (error)
		return error;
	
	pipeline.shaderSet.push_back(buffShader);

	error = glProgram.setupPipeline(pipeline);
	if (error)
		return error;

	return std::nullopt;
}
