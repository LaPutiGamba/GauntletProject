#include <iostream>
#include "SceneDirector.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
//#include "Timer.h"

unsigned int _globalElapsedTime = -10;
bool _gameOn = true;
SceneDirector* _sceneDirector = NULL;
InputManager* _inputManager = NULL;
ResourceManager* _resourceManager = NULL;
SoundManager* _soundManager = NULL;

int main(int argc, char* argv[]) { 
	// INITS 
	// Singletons
	_sceneDirector = SceneDirector::GetInstance();
	_inputManager = InputManager::GetInstance();
	_resourceManager = ResourceManager::GetInstance();
	_soundManager = SoundManager::GetInstance();
	
	// Init Time Control
	//Timer* globalTimer = new Timer();
	//globalTimer->start();
	//Uint32 lastTime = 0;

	// MAIN LOOP
	while (_gameOn){
		// REINIT OR NOT
		if(_sceneDirector->GetCurrentScene()->MustReInit()){
			_sceneDirector->GetCurrentScene()->ReInit();
		}

		// READ CONTROLS
		_inputManager->Update();
		
		// UPDATE TIME
		//unsigned int actualTime = globalTimer->GetTicks();
		//_globalElapsedTime = actualTime - lastTime;
		//lastTime =  actualTime;
		
		// UPDATE SCENE
		_sceneDirector->GetCurrentScene()->Update();

		// REINIT OR NOT
		if(!_sceneDirector->GetCurrentScene()->MustReInit()){
			_sceneDirector->GetCurrentScene()->Render();
		}
	}

	return 0;
}

