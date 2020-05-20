#include "SystemManager.h"

int DefaultTargetFPS = 60;
GlobalSystemManager g_manager;

ErrorList GlobalSystemManager::init()
{
	ErrorList errors;
	errors += window.init();
	errors += glManager.init();

	int bufferSizeX, bufferSizeY;
	window.getBufferSize(bufferSizeX, bufferSizeY);
	glManager.setViewportSize(bufferSizeX, bufferSizeY);
	fpsController.setTargetFPS(DefaultTargetFPS);

	errors += scene.loadScene("resources/scenes/default.xml");
	errors += scene.init();

	return errors;
}

ErrorList GlobalSystemManager::loop()
{
	while (!window.shouldClose()) {
		window.setTitle(std::string("fps: ") + std::to_string((int)fpsController.getSmoothFPS()));
		window.poll();
		glManager.clearFrame();
		scene.update(fpsController.getFrameDelta());
		glManager.flush();
		window.draw();
		fpsController.seek();
	}

	return ErrorList();
}

ErrorList GlobalSystemManager::free()
{
	scene.reset();
	return ErrorList();
}

Window& GlobalSystemManager::GetWindow()
{
	return window;
}

FPSController& GlobalSystemManager::GetFPSController()
{
	return fpsController;
}
