#pragma once
#include <vector>
#include "Scene.h"

//! Enum Scenes.
/*! All the Scenes in the game. */
enum SceneEnum {
	MAIN, OPTIONS, SAVE_LOAD, INTRO, GAME, GAMEOVER,
	_LASTSCENE
};

#define NUM_SCENES _LASTSCENE

class SceneDirector
{
	public:
		~SceneDirector();

		void Init();
		
		void ChangeScene(SceneEnum nextScene, bool reInit = true);

		SceneEnum GetCurrentSceneNum() { return _currentScene; };

		Scene* GetCurrentScene() { return _vectorScenes[_currentScene]; };
		
		// Gets pointer to instance (SINGLETON)
		static SceneDirector* GetInstance() {
			if (_pInstance == NULL) {
				_pInstance = new SceneDirector();
			}
			return _pInstance;
		}
	protected:
		SceneDirector();
		static SceneDirector* _pInstance; // Pointer to instance (SINGLETON)

		std::vector<Scene*>	_vectorScenes; // Vector with all the scenes of the game
		SceneEnum _currentScene; // Current scene
};