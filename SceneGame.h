#pragma once
#include "Scene.h"
#include "Player.h"
#include "EnemyGhost.h"
#include "Camera.h"
#include "GameState.h"

class SceneGame : public Scene
{
private:
	int _actualMapID; ///< The actual map ID
	Player* _player; ///< The player
	Camera _camera; ///< The camera
	EnemyGhost* _enemy; ///< The enemy
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