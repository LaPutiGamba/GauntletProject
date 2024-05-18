#pragma once
#include "Scene.h"
#include "GameState.h"
#include "Camera.h"
#include <vector>
#include <string>

class SceneGame : public Scene
{
private:
	int _actualMapID; ///< The actual map ID
	class Player* _player; ///< The player
	class Camera _camera; ///< The camera
	std::vector<class Enemy*> _pEnemies; ///< The enemies array
	std::vector<class Object*> _pObjects; ///< The objects array
	std::string _playerName; ///< The player name
	bool _bIsNameSet; ///< The name set
	int _selectedKeyboardKey; ///< The selected keyboard key

	/// \brief Save the score
	void SaveScore(std::string name, int points);

	/// \brief Read the level info
	int ReadLevelInfo(const char* filename);

	/// \brief Print Keyboard
	void PrintKeyboard();

protected:
	GameState::PlayerSelected _playerSelected; ///< The selected player

public:
	SceneGame();
	~SceneGame();

	void Init() override;
	void ReInit() override;
	void Update() override;
	void Render() override;

	Camera* GetCamera() { return &_camera; }
};