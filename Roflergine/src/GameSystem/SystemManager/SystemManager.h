#pragma once
#include "../../Utils/FPSController.h"
#include "../../GLTool/GLManager.h"
#include "../../Window/Window.h"
#include "../GameScene.h"


class GlobalSystemManager {
public:
	
	ErrorList init();
	ErrorList loop();
	ErrorList free();

	Window& GetWindow();
	FPSController& GetFPSController();


private:
	GameScene scene;
	Window window;
	FPSController fpsController;
	GLManager glManager;
};

extern GlobalSystemManager g_manager;
