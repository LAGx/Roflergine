#include "GameObjectRegister.h"
#include "GameObject/GraphicGameObject.h"
#include "GameObject/CameraObject.h"
#include "GameObject/GraphicObjectRotator.h"
#include "GameObject/Light/AmbientLightSource.h"
#include "GameObject/Light/DirectionalLightsource.h"

GameObjectRegister::IntefaceDecompositionPointer GameObjectRegister::Generate(const char* className){
	IntefaceDecompositionPointer decomposition;

	if (strcmp(className, GraphicGameObject::GetClassName()) == 0) {
		GraphicGameObject* object = new GraphicGameObject();
		decomposition.core = reinterpret_cast<void*>(object);
		decomposition.as_game_object = dynamic_cast<IGameObject*>(object);
		decomposition.as_phisic_object = dynamic_cast<IPhisicSimulatable*>(object);
	}
	else if (strcmp(className, CameraObject::GetClassName()) == 0) {
		CameraObject* object = new CameraObject();
		decomposition.core = reinterpret_cast<void*>(object);
		decomposition.as_game_object = dynamic_cast<IGameObject*>(object);
		decomposition.as_phisic_object = dynamic_cast<IPhisicSimulatable*>(object);
	}
	else if (strcmp(className, GraphicObjectRotator::GetClassName()) == 0) {
		GraphicObjectRotator* object = new GraphicObjectRotator();
		decomposition.core = reinterpret_cast<void*>(object);
		decomposition.as_game_object = dynamic_cast<IGameObject*>(object);
		decomposition.as_phisic_object = dynamic_cast<IPhisicSimulatable*>(object);
	}
	else if (strcmp(className, AmbientLightSource::GetClassName()) == 0) {
		AmbientLightSource* object = new AmbientLightSource();
		decomposition.core = reinterpret_cast<void*>(object);
		decomposition.as_game_object = dynamic_cast<IGameObject*>(object);
		decomposition.as_phisic_object = dynamic_cast<IPhisicSimulatable*>(object);
	}
	else if (strcmp(className, DirectionalLightSource::GetClassName()) == 0) {
		DirectionalLightSource* object = new DirectionalLightSource();
		decomposition.core = reinterpret_cast<void*>(object);
		decomposition.as_game_object = dynamic_cast<IGameObject*>(object);
		decomposition.as_phisic_object = dynamic_cast<IPhisicSimulatable*>(object);
	}

	return decomposition;
}