#include <iostream>
#include "SceneDirector.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Timer.h"
//#include "Timer.h"

#define FPS 30

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
	Timer* globalTimer = new Timer();
	globalTimer->StartTimer();
	unsigned int lastTime = 0, deltaTime, currentTime;
	float msFrame = 1 / (FPS / 1000.0f);

	// MAIN LOOP
	while (_gameOn){
		// REINIT OR NOT
		if(_sceneDirector->GetCurrentScene()->MustReInit())
			_sceneDirector->GetCurrentScene()->ReInit();

		// READ CONTROLS
		_inputManager->Update();
		
		// UPDATE TIME
		currentTime = globalTimer->GetTicks();
		deltaTime = currentTime - lastTime;
		if (deltaTime < static_cast<unsigned int>(msFrame)) 
			SDL_Delay((int)msFrame - deltaTime);
		lastTime =  globalTimer->GetTicks();
		
		// UPDATE SCENE
		_sceneDirector->GetCurrentScene()->Update();

		// REINIT OR NOT
		if(!_sceneDirector->GetCurrentScene()->MustReInit())
			_sceneDirector->GetCurrentScene()->Render();
	}

	return 0;
}

