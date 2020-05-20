#pragma once
#include <vector>
#include "IGameObject.h"
#include <filesystem>
#include "../Utils/TimeValue.h"
#include "../Phisic/PhisicWorld.h"
#include "GameObjectRegister.h"
#include "../Shader/ShaderManager.h"
#include "../GLTool/GLProgram.h"


class GameScene {
public:
	GameScene();
	~GameScene();

	ErrorList loadScene(const std::filesystem::path&);
	ErrorList init();
	void update(DeltaTimeValue delta);
	void reset();

private:
	Error setupGLProgram();

	std::vector<GameObjectRegister::IntefaceDecompositionPointer> objects_usage;
	std::vector<IGameObject*> objects;
	GLProgram glProgram;
	PhisicWorld phisicWorld;
};