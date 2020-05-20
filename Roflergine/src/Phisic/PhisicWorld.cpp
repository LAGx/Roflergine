#include "PhisicWorld.h"

void PhisicWorld::registerObject(IPhisicSimulatable* obj){
	if(obj != nullptr)
		objects.emplace(obj);
}


void PhisicWorld::unregisterObject(IPhisicSimulatable* obj){
	if (obj != nullptr)
		objects.erase(obj);
}

void PhisicWorld::simulate(DeltaTimeValue delta){
	for (auto& obj : objects)
		obj->simulate(delta);
}
