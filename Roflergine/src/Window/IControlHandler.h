#pragma once

class IControlHandler {
public:
	virtual void OnKeyButtonPressed(int key) {}
	virtual void OnKeyButtonPressing(int key) {}
	virtual void OnMouseMovement(double x, double y) {}
};