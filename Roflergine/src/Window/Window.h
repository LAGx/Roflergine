#pragma once
#include <GLFW/glfw3.h>
#include "../Utils/Error.h"
#include <string>
#include <memory>
#include <set>
#include "IControlHandler.h"


class Window {
public:

	Error init();

	void getBufferSize(int& x, int& y);
	void setTitle(std::string);
	bool shouldClose() const;
	void poll();
	void draw();
	double getAspectRatio() const;

	void registerListener(IControlHandler*);
	void unregisterListener(IControlHandler*);

	~Window();
private:

	void cleanup();
	static void handleKey(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleCursor(GLFWwindow* window, double x, double y);

	GLFWwindow* instance = nullptr;
	struct {
		int x = 1500;
		int y = 900;
	}size;
	std::string name = "default";
	bool wasInit = false;

	std::set<IControlHandler*> keyEventListeners;
	std::set<int> pressingKey;
};