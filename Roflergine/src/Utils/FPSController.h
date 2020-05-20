#pragma once
#include "TimeValue.h"
#include "../Math/NumberCircle.h"


typedef f64 FPS;

class FPSController {
public:
	FPSController();
	void setTargetFPS(FPS);
	FPS getSmoothFPS();
	DeltaTimeValue getFrameDelta();
	void seek();

private:
	
	FPS deltaToFPS(DeltaTimeValue);
	DeltaTimeValue FPSToDelta(FPS);

	DeltaTimeValue targetDelta;
	DeltaTimeValue payloadDeltaTime;
	DeltaTimeValue summaryDelta;

	std::chrono::time_point<std::chrono::steady_clock> lastTime;

	NumberCircle<FPS, 20> smoothFps;
};