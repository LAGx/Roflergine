#pragma once
#include "../Utils/TimeValue.h"
#include <algorithm>
#include "IPhisicSimutatable.h"
#include <set>

class PhisicWorld {
public:
	void registerObject(IPhisicSimulatable*);
	void unregisterObject(IPhisicSimulatable*);
	void simulate(DeltaTimeValue);

private:
	std::set<IPhisicSimulatable*> objects;
};