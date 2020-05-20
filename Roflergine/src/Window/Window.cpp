#include "Window.h"
#include <functional>
#include <iostream>

using namespace std;

Error Window::init() {

	if (wasInit)
		return nullopt;
	wasInit = true;

	auto initCode = glfwInit();

	if (initCode != GLFW_TRUE) {
		cleanup();
		return { {"Can`t init glfw. init code: " + to_string(initCode) + ".", ErrorCode::Init} };
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	instance = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);

	if (!instance) {
		cleanup();
		return { { "GLFW Can`t create window." , ErrorCode::Init} };
	}

	glfwMakeContextCurrent(instance);

	glfwSetInputMode(instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(instance, this);
	glfwSetKeyCallback(instance, handleKey);
	glfwSetCursorPosCallback(instance, handleCursor);

	return nullopt;
}


void Window::getBufferSize(int& x, int& y) {
	if(instance != nullptr)
		glfwGetFramebufferSize(instance, &x, &y);
}

void Window::setTitle(std::string title){
	if(instance != nullptr)
		glfwSetWindowTitle(instance, title.c_str());
}

bool Window::shouldClose() const{
	return instance != nullptr && glfwWindowShouldClose(instance);
}

void Window::poll() {
	glfwPollEvents();

	for (auto key : pressingKey) 
		for (auto handler : keyEventListeners)
			handler->OnKeyButtonPressing(key);
	
}

void Window::draw() {
	if(instance != nullptr)
		glfwSwapBuffers(instance);
}

double Window::getAspectRatio() const
{
	return static_cast<double>(size.x)/static_cast<double>(size.y);
}

void Window::cleanup() {
	if (!wasInit)
		return void();
	wasInit = false;
	glfwTerminate();
}

void Window::handleKey(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS) {
		self->pressingKey.emplace(key);

		for (auto handler : self->keyEventListeners)
			handler->OnKeyButtonPressed(key);
	}

	if (action == GLFW_RELEASE)
		self->pressingKey.erase(key);
}

void Window::handleCursor(GLFWwindow* window, double x, double y)
{
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

	for (auto handler : self->keyEventListeners)
		handler->OnMouseMovement(x, y);
}

void Window::registerListener(IControlHandler* obj){
	if(obj != nullptr)
		keyEventListeners.emplace(obj);
}

void Window::unregisterListener(IControlHandler* obj){
	if (obj != nullptr)
		keyEventListeners.erase(obj);
}

Window::~Window() {
	cleanup();
}