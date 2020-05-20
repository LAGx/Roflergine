#include "FPSController.h"

FPSController::FPSController()
{
	lastTime = GetTimeNow();
}

void FPSController::setTargetFPS(FPS target){
	targetDelta = FPSToDelta(target);
}

FPS FPSController::getSmoothFPS(){
	smoothFps.setNext(deltaToFPS(summaryDelta));
	return smoothFps.getMean();
}

DeltaTimeValue FPSController::getFrameDelta(){
	return summaryDelta;
}

void FPSController::seek(){
	payloadDeltaTime = GetDeltaToNow(lastTime);
	
	summaryDelta = payloadDeltaTime;
	auto sleepToTarget = targetDelta - payloadDeltaTime;

	if (sleepToTarget > DeltaTimeValue::Zero()) {
		SleepThread(sleepToTarget);
		summaryDelta += sleepToTarget;
	}

	lastTime = GetTimeNow();
}

FPS FPSController::deltaToFPS(DeltaTimeValue delta){
	return 1.0 / delta.GetSeconds<FPS>();
}

DeltaTimeValue FPSController::FPSToDelta(FPS fps){
	return DeltaTimeValue::Seconds(i64(1)) / fps;
}