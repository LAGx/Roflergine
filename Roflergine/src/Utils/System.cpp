#include "System.h"
#include "TimeValue.h"

std::chrono::time_point<std::chrono::steady_clock> GetTimeNow() {
	return std::chrono::high_resolution_clock::now();
}

DeltaTimeValue GetDeltaToNow(const std::chrono::time_point<std::chrono::steady_clock>& past) {
	return DeltaTimeValue::Microseconds<i64>(std::chrono::duration_cast<std::chrono::microseconds>(GetTimeNow() - past).count());
}

DeltaTimeValue GetDeltaTime(const std::chrono::time_point<std::chrono::steady_clock>& future, const std::chrono::time_point<std::chrono::steady_clock>& past) {
	return DeltaTimeValue::Microseconds<i64>(std::chrono::duration_cast<std::chrono::microseconds>(future - past).count());
}

void SleepThread(const DeltaTimeValue& delta) {
	std::this_thread::sleep_for(std::chrono::microseconds(delta.GetMicroseconds<i64>()));
}
