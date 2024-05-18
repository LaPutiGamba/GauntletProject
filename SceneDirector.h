#pragma once
#include <vector>
#include "Scene.h"

/// \enum SceneEnum
/// \brief Enum with all the scenes of the game
/// \note MAIN, OPTIONS, SAVE_LOAD, HIGHSCORE, GAME, GAMEOVER
enum SceneEnum {
	MAIN, OPTIONS, SAVE_LOAD, HIGHSCORE, GAME, GAMEOVER,
	_LASTSCENE
};

#define NUM_SCENES _LASTSCENE

/// \class SceneDirector
/// \brief Handles the load and management of the scenes in the game
class SceneDirector
{
protected:
	std::vector<Scene*>	_vectorScenes; ///< Vector with all the scenes of the game
	SceneEnum _currentScene; ///< Current scene
	static SceneDirector* _pInstance; ///< Singleton instance 

public:
	~SceneDirector();

	/// \brief Initialize the scenes
	void Init();
	
	/// \brief Change the current scene
	/// \param Scene to change
	/// \param True to reinitialize the scene 
	void ChangeScene(SceneEnum nextScene, bool reInit = true);

	/// \brief Get the current scene number
	/// \return Current scene number
	SceneEnum GetCurrentSceneNum() { return _currentScene; };

	/// \brief Get the current scene
	/// \return Current scene
	Scene* GetCurrentScene() { return _vectorScenes[_currentScene]; };
		
	///	\brief Singleton instance getter
	///	\return Singleton instance
	static SceneDirector* GetInstance() {
		if (_pInstance == NULL) {
			_pInstance = new SceneDirector();
		}
		return _pInstance;
	}

protected:
	SceneDirector();
};