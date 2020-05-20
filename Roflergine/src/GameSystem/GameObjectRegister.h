#pragma once
#include "IGameObject.h"
#include "../Phisic/IPhisicSimutatable.h"

class GameObjectRegister {
public:

	struct IntefaceDecompositionPointer{
		void* core = nullptr;
		IGameObject* as_game_object = nullptr;
		IPhisicSimulatable* as_phisic_object = nullptr;
	};

	static IntefaceDecompositionPointer Generate(const char* className);
};
