#pragma once
#include "../Utils/TimeValue.h"


class IPhisicSimulatable {
public:
	virtual void simulate(DeltaTimeValue) = 0;
};