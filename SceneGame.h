#pragma once
#include "Scene.h"
#include "GameState.h"
#include "Camera.h"
#include <vector>

class SceneGame : public Scene
{
private:
	int _actualMapID; ///< The actual map ID
	class Player* _player; ///< The player
	class Camera _camera; ///< The camera
	std::vector<class Enemy> _enemies; ///< The enemies array
	std::vector<class Object*> _objects; ///< The objects array

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

	int ReadLevelInfo(const char* filename);
};